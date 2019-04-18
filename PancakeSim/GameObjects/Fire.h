#pragma once

#include "Components/SpriteAnimator.h"

class FVector2;

class Fire : public SpriteAnimator
{
public:
	Fire(SpriteSheet* sprite);
	~Fire();

	virtual void Begin() override;
	// @Param flameSize : in %
	void Update(float flameSize);

	float GetFlameSize();

	void SetInvervalLength(float len);

private:

	Vector2* startPosition;

	float updateIntervalLength = 0.1f;
	float currentInterval = 0;

	int currentSpriteId = 0;

	const float minFlameSize = 0.85f;
	const float maxFlameSize = 1.25f;
	float currentFalmeSize = 1.0f;

};

