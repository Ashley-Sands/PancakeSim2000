#pragma once
#include "Components/SpriteAnimator.h"

class SpriteSheet;

class Jug : public SpriteAnimator
{
public:
	Jug(SpriteSheet* sprite);
	~Jug();

	virtual void Begin() override;
	void Update(int rot);

	float Pour();

private:
	const float max_mixture = 100.0f;
	float currentMixture = 100.0f;

	const float maxPourRate = 10.0f;

	float currentRotation = 0;
	const float minRotation = 5;				// min rotaiton to start pouring
	const float maxRotation = 180;				// max pour rotation
	const float rotationMultiplier = 0.25f;		// rotation position multiplyer

};

