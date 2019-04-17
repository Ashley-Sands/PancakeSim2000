#pragma once

#include "Components/SpriteAnimator.h"

class Fire : public SpriteAnimator
{
public:
	Fire(SpriteSheet* sprite);
	~Fire();

	// @Param flameSize : in %
	void Update(float flameSize);

private:

	float updateIntervalLength = 0.1f;
	float currentInterval = 0;

	int currentSpriteId = 0;

	const float minFlameSize = 0.25f;
	const float maxFlameSize = 1.3f;
	float currentFalmeSize = 0.25;

};

