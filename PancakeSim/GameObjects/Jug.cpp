#include "Jug.h"
#include "Components/SpriteSheet.h"


Jug::Jug(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
}


Jug::~Jug()
{
}

void Jug::Begin()
{
	SpriteAnimator::Begin();
	GetSpriteSheet()->GetSpriteRectByID(0, currentSpritePos);
}