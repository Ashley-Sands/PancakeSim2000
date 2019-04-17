#include "Fire.h"
#include "Components/Time.h"
#include "Components/SpriteSheet.h"


Fire::Fire(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
}


Fire::~Fire()
{
}

void Fire::Update()
{
	currentInterval += Time::GetDeltaSeconds();

	// has enoght time pased to update the sprite
	if (currentInterval < updateIntervalLength) return;

	//if so go to the next sprite or loop back to the state if we have reached the end of spriteSheet

	currentInterval -= updateIntervalLength;
	currentSpriteId++;

	SpriteSheet* spriteSheet = GetSpriteSheet();

	if ( currentSpriteId >= spriteSheet->GetTotalSprites() )
		currentSpriteId = 0;

	spriteSheet->GetSpriteRectByID(currentSpriteId, /*out*/ currentSpritePos);

}
