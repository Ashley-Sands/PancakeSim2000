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
	printf("Sprite %s loaded seccessful; Texture Size X: %i Y: %i \n", path.c_str(), spriteSize->x, spriteSize->y);
}

SDL_Texture* Sprite::GetSprite()
{
	return spriteTexture;
}

Vector2* Sprite::GetSpriteSize()
{
	return spriteSize;
}

void Sprite::RenderSprite(SDL_Renderer* renderer, SDL_Rect* destRect, int angle /* = 0 */, SDL_Rect* srcRect /* = NULL */)
{

	SDL_RenderCopyEx(renderer, spriteTexture, srcRect, destRect, angle, NULL, SDL_FLIP_NONE);


}