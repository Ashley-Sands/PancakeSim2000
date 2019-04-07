#include "Pancake.h"
#include "Components/SpriteSheet.h"
#include "Components/Sprite.h"

Pancake::Pancake(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
}


Pancake::~Pancake()
{
}

void Pancake::Update(float inputValue)
{
	SpriteSheet* spriteSheet = GetSpriteSheet();
	int spriteID = spriteSheet->GetSpriteIdByPercentage(inputValue);

	spriteSheet->GetSpriteRectByID(spriteID, currentSpritePos);

}