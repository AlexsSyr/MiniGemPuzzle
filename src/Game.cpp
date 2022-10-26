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
	window = SDL_CreateWindow("MiniGemPuzzle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, windowInitFlags);

	if (window == nullptr)
	{
		Exception::Throw(std::format("SDL_CreateWindow failed: {} !", SDL_GetError()));
	}

	render.Initialize(window);
	render.SetClearColor(0xAA, 0xAA, 0xAA);

	gameField = GameFieldLoader::LoadField("Levels//Level1.lvl");

	int32 windowW = 0;
	int32 windowH = 0;
	SDL_GetWindowSize(window, &windowW, &windowH);

	gameField.UpdateGrid(windowW, windowH);

	player.Initialize(playerInput, gameField, 
		[this]()
		{
			Victory();
		});
}

void Game::Run()
{
	SDL_Event event;

	while (run)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				run = false;
				break;
			}
			case SDL_WINDOWEVENT:
			{
				if (event.window.event != SDL_WINDOWEVENT_RESIZED)
					break;

				int32 windowW = 0;
				int32 windowH = 0;
				SDL_GetWindowSize(window, &windowW, &windowH);

				gameField.UpdateGrid(windowW, windowH);

				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				int32 mousePosX = 0;
				int32 mousePosY = 0;
				const Uint32 mouseButtons = SDL_GetMouseState(&mousePosX, &mousePosY);

				if (mouseButtons | SDL_BUTTON_LMASK)
					playerInput.MouseButtonDown(mousePosX, mousePosY);

				break;
			}
			}
		}
		
		render.Clear();
		render.DrawField(gameField);
		render.Present();
	}
}

void Game::Exit()
{
	render.Release();

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

void Game::Victory()
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Victory !", "Victory !", window);
	gameField = GameFieldLoader::LoadField("Levels//Level1.lvl");

	int32 windowW = 0;
	int32 windowH = 0;
	SDL_GetWindowSize(window, &windowW, &windowH);
	gameField.UpdateGrid(windowW, windowH);
}
