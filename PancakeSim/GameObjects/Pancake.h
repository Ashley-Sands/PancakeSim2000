#pragma once
#include "Components/SpriteAnimator.h"

class Pancake : public SpriteAnimator
{
public:

	Pancake(SpriteSheet* sprite);
	~Pancake();

	void Update(float inputValue);


};

