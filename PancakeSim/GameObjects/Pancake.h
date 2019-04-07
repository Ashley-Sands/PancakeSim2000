#pragma once
#include "Components/SpriteAnimator.h"

class Rigidbody;
class Time;

class Pancake : public SpriteAnimator
{
public:

	Pancake(SpriteSheet* sprite, Time* time);
	~Pancake();

	void Update(float inputValue);


private:
	Rigidbody* rigidbody;
	
	float GetFlipPercentage();	// Get the flip playback position in %

	float flipLength = 2;
	float currentFlip = 0;
	float flipForce = 1;
	float counterForce = 0.6f;

	Time* time;
};

