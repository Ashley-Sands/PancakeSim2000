#include "Jug.h"
#include "Components/SpriteSheet.h"
#include "Components/Time.h"
#include "Components/Helper.h"

Jug::Jug(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
}


Jug::~Jug()
{
}

void Jug::Begin()
{
	SpriteAnimator::Begin();
}

void Jug::Update(int rotation)
{

	currentRotation = Helper::Clamp(-maxRotation, 10, rotation);

	SetRotation( currentRotation * rotationMultiplier);

	// Get the correct sprite for the amount of mixture we have :P
	int currentSpriteId = GetSpriteSheet()->GetSpriteIdByPercentage( (1.0f-(currentMixture / max_mixture)) );
	GetSpriteSheet()->GetSpriteRectByID(currentSpriteId, currentSpritePos);
}

float Jug::Pour()
{

	if (currentMixture <= 0.0f) return 0;

	float pourRate = 0;
	float rotation = abs( Helper::Clamp(-maxRotation, 0, currentRotation) );

	if(rotation > minRotation)
		pourRate = ( maxPourRate * (rotation / maxRotation) ) * Time::GetDeltaSeconds();

	if (pourRate > currentMixture) pourRate = currentMixture;

	currentMixture -= pourRate;

	if (currentMixture < 0.0f)
		currentMixture = 0;

	return pourRate;

}