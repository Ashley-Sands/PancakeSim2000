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

};

