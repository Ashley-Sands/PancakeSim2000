#include "Sprite.h"

#include "SDL.h"
#include "SDL_image.h"

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
	if(spriteSurface != NULL)
		SDL_FreeSurface(spriteSurface);

}

void Sprite::SetSprite( std::string path, SDL_PixelFormat* pixelFormat)
{
	// free the surface if one alread exist
	if (spriteSurface != NULL)
	{
		SDL_FreeSurface(spriteSurface);
		spriteSurface = NULL;
	}


	// Load and optimize surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
		printf("Faild to load img! (%s)", path.c_str());
	else
		spriteSurface = SDL_ConvertSurface(loadedSurface, pixelFormat, NULL);
	
	SDL_FreeSurface(loadedSurface);

}

SDL_Surface* Sprite::GetSprite()
{
	return spriteSurface;
}