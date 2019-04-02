#include "SpriteSheet.h"
#include "Vector2.h"

#include "SDL.h"
#include "SDL_image.h"


SpriteSheet::SpriteSheet()
{
}

SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::SetSpriteSize( int width )
{

	int spriteSheetWidth = GetSpriteSize()->x;

	totalSprites = spriteSheetWidth / width;
	spriteSize->x = width;	//update the sprite size to match the size of a single sprite.
}

void SpriteSheet::GetSpriteRectByID(int id, SDL_Rect* outRect)
{

	outRect->w = GetSpriteSize()->x;
	outRect->h = GetSpriteSize()->y;

	outRect->x = GetSpriteSize()->x * id;
	outRect->y = 0;

}

float SpriteSheet::GetSpriteIdByPercentage(float percentage)
{

	return floor( (totalSprites - 1.0f) * percentage );

}
