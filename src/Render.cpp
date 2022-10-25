#include "Render.h"
#include "Miscs/Exception.h"
#include "GameField.h"

#include <format>
#include <SDL.h>
#include <math.h>

void Render::Initialize(SDL_Window* const window) 
{
	if(window == nullptr)
		Exception::Throw(std::format("SDL_CreateRenderer failed: {}!", "window is nullptr!"));

	this->window = window;

	const int32 renderDriverIndex = -1;
	const uint32 renderInitFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	render = SDL_CreateRenderer(window, renderDriverIndex, renderInitFlags);

	if (render == nullptr)
		Exception::Throw(std::format("SDL_CreateRenderer failed: {}!", SDL_GetError()));
}

void Render::Release()
{
	if (render)
		SDL_DestroyRenderer(render);
}

void Render::SetClearColor(uint8 r, uint8 g, uint8 b)
{
	clearColor = { r, g, b };
}

void Render::Clear()
{
	SDL_SetRenderDrawColor(render, clearColor.r, clearColor.g, clearColor.b, 0x00);
	SDL_RenderClear(render);
}

void Render::Present()
{
	SDL_RenderPresent(render);
}

void Render::DrawField(const GameField& gameField)
{
	int32 canvasW = 0;
	int32 canvasH = 0;

	SDL_GetWindowSize(window, &canvasW, &canvasH);

	if (canvasW == 0 || canvasH == 0)
		return;

	const int32 cellSize = std::min(canvasW, canvasH) * 0.15;
	const uint32 fieldSize = gameField.GetSize();
	const uint32 gridPosX = (canvasW - cellSize * fieldSize) / 2;
	const uint32 gridPosY = (canvasH - cellSize * fieldSize) / 2;

	SDL_Rect rectangle = 
	{
		.w = cellSize,
		.h = cellSize
	};

	for(uint32 i = 0; i < fieldSize; ++i)
		for (uint32 j = 0; j < fieldSize; ++j)
		{
			rectangle.x = gridPosX + j * cellSize;
			rectangle.y = gridPosY + i * cellSize;

			DrawFieldCell(rectangle, gameField, i, j);
		}
}

void Render::DrawFieldCell(const SDL_Rect& rectangle, const GameField& gameField, uint32 posX, uint32 posY)
{

	const GameFieldCellType cellType = gameField.GetCellType(posX, posY);

	switch (cellType)
	{
	case GameFieldCellType::FREE:
		SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
		break;
	case GameFieldCellType::BLOCK:
		SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00);
		break;
	case GameFieldCellType::GEM_1:
		SDL_SetRenderDrawColor(render, 0xFF, 0x00, 0x0, 0xFF);
		break;
	case GameFieldCellType::GEM_2:
		SDL_SetRenderDrawColor(render, 0x00, 0xFF, 0x00, 0xFF);
		break;
	case GameFieldCellType::GEM_3:
		SDL_SetRenderDrawColor(render, 0x00, 0x00, 0xFF, 0xFF);
		break;
	default:
		break;
	}

	SDL_RenderFillRect(render, &rectangle);

	SDL_SetRenderDrawColor(render, clearColor.r, clearColor.g, clearColor.b, 0xFF);
	SDL_RenderDrawRect(render, &rectangle);
}
