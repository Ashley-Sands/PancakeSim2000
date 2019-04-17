#include "Fire.h"
#include "Components/Time.h"
#include "Components/SpriteSheet.h"
#include "Components/Vector2.h"

Fire::Fire(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
	startPosition = new Vector2();
}


Fire::~Fire()
{

	delete startPosition;

}

void Fire::Begin()
{

	SpriteAnimator::Begin();

	startPosition->x = GetPosition()->x;
	startPosition->y = GetPosition()->y;

}

void Fire::Update(float flameSize_percentage)
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

	currentFalmeSize = minFlameSize + ((maxFlameSize - minFlameSize) * flameSize_percentage);

	// scale flame size
	SetScale(currentFalmeSize, currentFalmeSize);
	SetAnchoredPosition(startPosition->x , startPosition->y , GetSpriteSheet()->GetSpriteSize()->x, GetSpriteSheet()->GetSpriteSize()->y );

}

float Fire::GetFlameSize()
{
	return currentFalmeSize;
}
