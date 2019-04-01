#pragma once
#include <String>

class SDL_Surface;
class SDL_PixelFormat;

// Loads and optimizes an image for SDL
class Sprite
{
public:
	Sprite();
	~Sprite();

	void SetSprite( std::string path, SDL_PixelFormat* pixelFormat );
	SDL_Surface* GetSprite();

private:
	SDL_Surface* spriteSurface;

};

