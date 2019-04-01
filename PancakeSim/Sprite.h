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
	virtual SDL_Surface* GetSprite();

protected:
	SDL_Surface* spriteSurface;

};

