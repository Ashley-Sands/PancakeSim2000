#pragma once
#include "Components/SpriteAnimator.h"

class SpriteSheet;

class Jug : public SpriteAnimator
{
public:
	Jug(SpriteSheet* sprite);
	~Jug();

	virtual void Begin() override;
	void Update();

	float Pour();

private:
	const float max_mixture = 100.0f;
	float currentMixture = 100.0f;

	const float maxPourRate = 25.0f;

};

