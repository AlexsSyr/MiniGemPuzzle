#include "Game.h"
#include "Miscs/Exception.h"
#include "Tools/GameFieldLoader.h"

#include <SDL.h>
#include <format>

void Game::Initialize()
{
	const uint32 initFlags = 0;
	const auto initError = SDL_Init(initFlags);

	if (initError)
	{
		Exception::Throw(std::format("SDL_Init failed: {} !", SDL_GetError()));
	}

	const uint32 windowInitFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	window = SDL_CreateWindow("Hello, SDL 2!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 1024, windowInitFlags);

	if (window == nullptr)
	{
		Exception::Throw(std::format("SDL_CreateWindow failed: {} !", SDL_GetError()));
	}

	gameField = GameFieldLoader::LoadField("Levels//Level1.lvl");
}

void Game::Run()
{
	SDL_Event event;

	while (run)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				run = false;
		}
	}
}

void Game::Exit()
{
	if (window)
	{
		SDL_DestroyWindow(window);
	}

	//Safe to call
	SDL_Quit();
}

SDL_Window* Game::GetWindow() const
{
	return window;
}
