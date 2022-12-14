#include "Render.h"
#include "Miscs/Exception.h"
#include "GameField.h"

#include <format>
#include <SDL.h>
#include "Tools/ImageLoader.h"
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

	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

	ImageLoader::Initialize();
	backgroundImage = ImageLoader::LoadImage(render, backgroundImgPath);
	ImageLoader::Release();

}

void Render::Release()
{
	if (backgroundImage)
		SDL_DestroyTexture(backgroundImage);

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
	SDL_RenderCopy(render, backgroundImage, nullptr, nullptr);

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

	canvasPos = gameField.GetCellCanvasPos(0, 0);

	rectangle.w *= 0.70;
	rectangle.h *= 0.70;

	rectangle.x = canvasPos.x + cellSize * 0.15;
	rectangle.y = canvasPos.y - cellSize;

	SDL_SetRenderDrawColor(render, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(render, &rectangle);

	canvasPos = gameField.GetCellCanvasPos(0, 2);
	rectangle.x = canvasPos.x + cellSize * 0.15;

	SDL_SetRenderDrawColor(render, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(render, &rectangle);

	canvasPos = gameField.GetCellCanvasPos(0, 4);
	rectangle.x = canvasPos.x; rectangle.x = canvasPos.x + cellSize * 0.15;

	SDL_SetRenderDrawColor(render, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(render, &rectangle);
}

void Render::DrawFieldCell(const SDL_Rect& rectangle, const GameField& gameField, uint32 posX, uint32 posY)
{

	const GameFieldCellType cellType = gameField.GetCellType(posX, posY);

	switch (cellType)
	{
	case GameFieldCellType::FREE:
		SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xDF);
		break;
	case GameFieldCellType::BLOCK:
		SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF);
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
