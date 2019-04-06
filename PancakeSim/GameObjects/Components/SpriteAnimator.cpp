#include "SpriteAnimator.h"
#include "SpriteSheet.h"


SpriteAnimator::SpriteAnimator(SpriteSheet* sprite) : SpriteObject(sprite)
{
}


SpriteAnimator::~SpriteAnimator()
{
}

SpriteSheet* SpriteAnimator::GetSpriteSheet()
{
	return (SpriteSheet*)sprite;
}