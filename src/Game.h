#pragma once
#include "GameField.h"
#include "Render.h"
#include "PlayerInput.h"

struct SDL_Window;

class Game
{
public:
	void Initialize();
	void Run();
	void Exit();

	SDL_Window* GetWindow() const;

private:
	bool run = true;
	SDL_Window* window = nullptr;
	GameField gameField;
	Render render;
	PlayerInput playerInput;
};