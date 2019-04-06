#include "SpriteAnimator.h"
#include "SpriteSheet.h"


SpriteAnimator::SpriteAnimator(SpriteSheet* sprite) : SpriteObject(sprite)
{
}


SpriteAnimator::~SpriteAnimator()
{
}

void SpriteAnimator::Update(Time* time)
{

}

SpriteSheet* SpriteAnimator::GetSpriteSheet()
{
	return (SpriteSheet*)sprite;
}