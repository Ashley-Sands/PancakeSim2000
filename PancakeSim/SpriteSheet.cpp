#include "SpriteSheet.h"

#include "SDL.h"
#include "SDL_image.h"


SpriteSheet::SpriteSheet()
{

	spriteWidth = 0;
	spriteSpacingX = 0;

}

SpriteSheet::SpriteSheet(int width, int spacingX)
{
	spriteWidth = width;
	spriteSpacingX = spacingX;
}


SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::SetSpriteSize( int width, int spacingX )
{
	spriteWidth = width;
	spriteSpacingX = spacingX;

	totalSprites = spriteSurface->clip_rect.x / spriteWidth; //?? //TODO this might no work as expected :| maybe use the function GetClipRect :)
															 // Also SpacingX is not taken into account, but for now who cares :)

}
