#include "SpriteSheet.h"
#include "Vector2.h"

#include "SDL.h"
#include "SDL_image.h"


SpriteSheet::SpriteSheet()
{

	spriteWidth = 0;

}

SpriteSheet::SpriteSheet(int width, int spacingX)
{
	spriteWidth = width;
}


SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::SetSpriteSize( int width, int spacingX )
{
	spriteWidth = width;

	int spriteSheetWidth = GetSpriteSize()->x;

	totalSprites = spriteSheetWidth / spriteWidth;

}

void SpriteSheet::GetSpriteRectByID(int id, SDL_Rect* outRect)
{

	outRect->h = GetSpriteSize()->x;
	outRect->w = spriteWidth;

	outRect->x = spriteWidth * id;
	outRect->y = 0;

}

float SpriteSheet::GetSpriteIdByPercentage(float percentage)
{

	return floor( (totalSprites - 1.0f) * percentage );

}
