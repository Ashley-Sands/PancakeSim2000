#include "Sprite.h"
#include "SDL_image.h"
#include "Vector2.h"


Sprite::Sprite()
{
	spriteSize = new Vector2(0, 0);
}


Sprite::~Sprite()
{

	SDL_DestroyTexture(spriteTexture);
	spriteTexture = NULL;

}

void Sprite::SetSprite(SDL_Renderer* renderer, std::string path )
{
	spriteTexture = IMG_LoadTexture(renderer, path.c_str());

	if (spriteTexture == NULL)
	{
		printf("Faled To Load Texture\n");
		return;
	}

	// get the sprite size 
	SDL_QueryTexture(spriteTexture, NULL, NULL, &spriteSize->x, &spriteSize->y);
	printf("\nSprite %s loaded seccessful; Texture Size X: %d Y: %d", path, spriteSize->x, spriteSize->y);
}

SDL_Texture* Sprite::GetSprite()
{
	return spriteTexture;
}

Vector2* Sprite::GetSpriteSize()
{
	return spriteSize;
}

void Sprite::RenderSprite(SDL_Renderer* renderer, SDL_Rect* destRect, SDL_Rect* srcRect /* = NULL */)
{

	SDL_RenderCopy(renderer, spriteTexture, srcRect, destRect);


}