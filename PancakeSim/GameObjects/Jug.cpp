#include "Jug.h"
#include "Components/SpriteSheet.h"
#include "Components/Time.h"

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

void Jug::Update()
{
	// Get the correct sprite for the amount of mixture we have :P
	int currentSpriteId = GetSpriteSheet()->GetSpriteIdByPercentage( (1.0f-(currentMixture / max_mixture)) );
	GetSpriteSheet()->GetSpriteRectByID(currentSpriteId, currentSpritePos);
}

float Jug::Pour()
{

	if (currentMixture <= 0.0f) return 0;

	float pourRate = maxPourRate * Time::GetDeltaSeconds();

	if (pourRate > currentMixture) pourRate = currentMixture;

	currentMixture -= pourRate;

	if (currentMixture < 0.0f) currentMixture = 0;

	return pourRate;

}