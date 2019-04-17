#pragma once

#include "Fire.h"

class FVector2;

class PanFire : public Fire
{
public:
	PanFire(SpriteSheet* sprite);
	~PanFire();

	void Update(FVector2* pancakePosition);
};

