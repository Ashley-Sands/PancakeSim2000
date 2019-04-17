#include "SpriteSheet.h"
#include "Vector2.h"

#include "SDL.h"
#include "SDL_image.h"


SpriteSheet::SpriteSheet() : Sprite()
{
}

SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::SetSpriteSize( int width, int height /*= -1 */)
{

	int spriteSheetWidth = GetSpriteSize()->x;
	int spriteSheetHeight = GetSpriteSize()->y;

	totalSprites = spriteSheetWidth / width;
	spriteSize->x = width;	//update the sprite size to match the size of a single sprite.

	if (height >= 0)
	{
		totalSpriteRows = spriteSheetHeight / height;
		spriteSize->y = height;
	}
	else
	{
		totalSpriteRows = 1;
	}
}

void SpriteSheet::GetSpriteRectByID(int id, SDL_Rect* outRect, int rowId /* = 0 */)
{

	outRect->w = GetSpriteSize()->x;
	outRect->h = GetSpriteSize()->y;

	outRect->x = GetSpriteSize()->x * id;
	outRect->y = GetSpriteSize()->y * rowId;

}

int SpriteSheet::GetSpriteIdByPercentage(float percentage) const
{
	//clamp the precentage to prevent us going out of range :)
	if (percentage < 0.0f) percentage = 0.0f;
	else if (percentage > 1.0f) percentage = 1.0f;

	// find the sprite id 
	int spriteId = floor((totalSprites) * percentage);;
	
	//prevent the id going over when precentage is == 1
	if (spriteId > totalSprites - 1)
		spriteId = totalSprites - 1;

	return spriteId;

}

int SpriteSheet::GetTotalSprites()
{
	return totalSprites;
}

int SpriteSheet::GetTotalSpriteRows()
{
	return totalSpriteRows;
}
