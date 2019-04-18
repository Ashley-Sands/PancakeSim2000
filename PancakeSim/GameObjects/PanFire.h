#pragma once

#include "Fire.h"
#include "Pancake.h"

class FVector2;

class PanFire : public Fire
{
public:
	PanFire(SpriteSheet* sprite);
	~PanFire();

	void Update(FVector2* pancakePosition, CookingState cookedState);

	// Renders current sprite from sheet to screen
	void virtual Render(SDL_Renderer* renderer) override;

private:

	bool canRender = false;

};

