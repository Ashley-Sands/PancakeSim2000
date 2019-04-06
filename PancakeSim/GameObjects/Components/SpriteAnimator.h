#pragma once
#include "SpriteObject.h"

class SpriteSheet;
class Time;

class SpriteAnimator : public SpriteObject
{
public:
	SpriteAnimator(SpriteSheet* sprite);
	~SpriteAnimator();

	SpriteSheet* GetSpriteSheet();

	// Renders current sprite from sheet to screen
	void virtual Render(SDL_Renderer* renderer) override;

protected:
	// the position whitin the spriteSheet
	SDL_Rect* currentSpritePos;

};

