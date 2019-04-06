#include "FryingPan.h"
#include "Components/SpriteSheet.h"
#include "Components/Sprite.h"


FryingPan::FryingPan(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
}


FryingPan::~FryingPan()
{
}

void FryingPan::Update(float inputValue)
{
	SpriteSheet* spriteSheet = GetSpriteSheet();
	int spriteID = spriteSheet->GetSpriteIdByPercentage(inputValue);
	
	spriteSheet->GetSpriteRectByID(spriteID, currentSpritePos);

}