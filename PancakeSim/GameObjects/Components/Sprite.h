#pragma once
#include <string>
#include "SDL.h"			// i dont why but the forwards declaration for SDL_Texture is not work, buts its fine if i include SDL.h, hmmmm.

class SDL_Surface;
class SDL_PixelFormat;
class SDL_Texture;
class SDL_Renderer;
class Vector2;

// Loads and optimizes an image for SDL
class Sprite
{
public:
	Sprite();
	~Sprite();

	void SetSprite(SDL_Renderer* renderer, std::string path);
	virtual SDL_Texture* GetSprite();
	
	Vector2* GetSpriteSize();

	/*
	* @Prama renderer:		renderer
	* @Prama destRect:		position and size on screen to render to
	* @Prama angle	 :		Angle to render sprite 
	* @Prama srcRect :		area of sprite to renderer
	*/
	void RenderSprite(SDL_Renderer* renderer, SDL_Rect* destRect, int angle = 0,  SDL_Rect* srcRect = NULL);

protected:

	SDL_Texture* spriteTexture;
	Vector2* spriteSize;

};

