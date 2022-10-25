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
	const uint32 fieldSize = gameField.GetSize();
	const uint32 cellSize = gameField.GetCellSize();

	SDL_Rect rectangle = 
	{
		.w = static_cast<int32>(cellSize),
		.h = static_cast<int32>(cellSize)
	};

	GameFieldCellCanvasPos canvasPos = { };

	for(uint32 i = 0; i < fieldSize; ++i)
		for (uint32 j = 0; j < fieldSize; ++j)
		{
			canvasPos = gameField.GetCellCanvasPos(i, j);

			rectangle.x = canvasPos.x;
			rectangle.y = canvasPos.y;

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

	if(posX * gameField.GetSize() + posY == gameField.GetSelectedCellIndex())
		SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0x00, 0xFF);

	SDL_RenderFillRect(render, &rectangle);

	SDL_SetRenderDrawColor(render, clearColor.r, clearColor.g, clearColor.b, 0xFF);
	SDL_RenderDrawRect(render, &rectangle);
}
