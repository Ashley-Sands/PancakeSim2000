#include "Sprite.h"

#include "SDL.h"
#include "SDL_image.h"

Sprite::Sprite()
{
}


Sprite::~Sprite()
{

}

void Sprite::SetSprite(SDL_Renderer* renderer, std::string path )
{
	spriteTexture = IMG_LoadTexture(renderer, path.c_str());

	if (spriteTexture == NULL)
	{
		printf("Faled To Load Texture");
		return;
	}

}

SDL_Texture* Sprite::GetSprite()
{
	return spriteTexture;
}


