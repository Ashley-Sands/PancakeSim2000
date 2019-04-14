#pragma once
#include "Components/SpriteAnimator.h"

class Rigidbody;

class Pancake : public SpriteAnimator
{
public:

	Pancake(SpriteSheet* sprite);
	~Pancake();

	void Update(float force, int panSpriteId);


private:
	Rigidbody* rigidbody;
	
	float GetFlipPercentage();	// Get the flip playback position in %

	float flipLength = 1.5;			//@ fliForce = 1
	float currentFlip = 0;
	
	const float flipForce = 4;
	float currentFlipForce = 0;
	float counterForce = 2.2f;

};

