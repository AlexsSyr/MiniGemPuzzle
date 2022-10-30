#pragma once
#include "../Miscs/Types.h"

struct SDL_Texture;
struct SDL_Renderer;

class ImageLoader
{
public:

	static void Initialize();
	static void Release();

	[[nodiscard]] static SDL_Texture* LoadImage(SDL_Renderer* const render, const Path& imgPath);

};