#pragma once

#include "GameObjects/Components/SpriteAnimator.h"

class Fire : public SpriteAnimator
{
public:
	Fire(SpriteSheet* sprite);
	~Fire();

	void Update();

private:

	float updateIntervalLength = 0.1f;
	float currentInterval = 0;

	int currentSpriteId = 0;

};

