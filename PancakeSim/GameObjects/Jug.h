#pragma once
#include "Components/SpriteAnimator.h"

class SpriteSheet;

class Jug : public SpriteAnimator
{
public:
	Jug(SpriteSheet* sprite);
	~Jug();

	virtual void Begin() override;
};

