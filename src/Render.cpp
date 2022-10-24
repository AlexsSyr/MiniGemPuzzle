#include "Render.h"
#include "Miscs/Exception.h"

#include <format>
#include <SDL.h>

void Render::Initialize(SDL_Window* const window)
{
	const int32 renderDriverIndex = -1;
	const uint32 renderInitFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	render = SDL_CreateRenderer(window, renderDriverIndex, renderInitFlags);

	if (render == nullptr)
		Exception::Throw("SDL_CreateRenderer failed!");
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
	Clear();
	Present();
}
