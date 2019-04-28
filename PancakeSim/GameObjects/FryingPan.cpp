#include "FryingPan.h"
#include "Components/SpriteSheet.h"
#include "Components/Sprite.h"
#include "Components/Vector2.h"

//Debuging
#include "Components/Debug/Console.h"

FryingPan::FryingPan(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
	startPosition = new FVector2();
}


FryingPan::~FryingPan()
{
	delete startPosition;
}

void FryingPan::Begin()
{
	SpriteAnimator::Begin();

	startPosition->x = GetPosition()->x;
	startPosition->y = GetPosition()->y;
}

void FryingPan::Update(float inputValue, float hobValue)
{
	SpriteSheet* spriteSheet = GetSpriteSheet();
	currentSpriteID = spriteSheet->GetSpriteIdByPercentage(inputValue);

	float offHobOffset = 100.0f * (1 - hobValue);	//TODO: Come on...

	spriteSheet->GetSpriteRectByID(currentSpriteID, /*out*/currentSpritePos);

	SetPosition(startPosition->x, startPosition->y - (offHobOffset));

}

int FryingPan::GetCurrentSpriteId()
{
	return currentSpriteID;
}

void FryingPan::SetPanBottom_LocalOffset(float offset)
{
	panBottom_localOffset = offset;
}

float FryingPan::GetPanBottom()
{
	return GetPosition()->y + panBottom_localOffset;
}
