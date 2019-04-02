#pragma once
#include "SpriteObject.h"

class SpriteSheet;
class Time;

class SpriteAnimator : public SpriteObject
{
public:
	SpriteAnimator(SpriteSheet* sprite);
	~SpriteAnimator();

	virtual void Update(Time* time, SDL_Renderer* renderer) override;



};

