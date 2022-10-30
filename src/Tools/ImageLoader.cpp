#include "ImageLoader.h"
#include <FreeImage.h>
#include "../Miscs/Exception.h"

#include <SDL.h>
#include <format>

void ImageLoader::Initialize()
{
	FreeImage_Initialise();
}

void ImageLoader::Release()
{
	FreeImage_DeInitialise();
}

SDL_Texture* ImageLoader::LoadImage(SDL_Renderer* const render, const Path& imgPath)
{
	const String pathString = imgPath.string();
	const char* path = pathString.c_str();

	FIBITMAP* bitMap = FreeImage_Load(FreeImage_GetFIFFromFilename(path), path, 0);

	if (bitMap == nullptr)
		Exception::Throw(std::format("FreeImage_Load failed: {}!", path));

	FIBITMAP* result = FreeImage_ConvertTo24Bits(bitMap);
	FreeImage_Unload(bitMap);

	FreeImage_FlipVertical(result);

	SDL_Texture* texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, FreeImage_GetWidth(result), FreeImage_GetHeight(result));
	SDL_UpdateTexture(texture, nullptr, FreeImage_GetBits(result), FreeImage_GetPitch(result));

	FreeImage_Unload(result);

	if(texture == nullptr)
		Exception::Throw(std::format("SDL_CreateTexture failed: {}!", SDL_GetError()));

	return texture;
}
