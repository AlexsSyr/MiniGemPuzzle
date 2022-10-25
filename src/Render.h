#pragma once
#include "Miscs/Types.h"

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Rect;

class GameField;

struct RenderClearColor
{
	uint8 r = 0xFF;
	uint8 g = 0xFF;
	uint8 b = 0xFF;
};

class Render
{
public:

	void Initialize(SDL_Window* const window);
	void Release();

	void SetClearColor(uint8 r, uint8 g, uint8 b);
	void Clear();
	void Present();

	void DrawField(const GameField& gameField);

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;
	RenderClearColor clearColor;

	void DrawFieldCell(const SDL_Rect& rectangle, const GameField& gameField, uint32 posX, uint32 posY);
};