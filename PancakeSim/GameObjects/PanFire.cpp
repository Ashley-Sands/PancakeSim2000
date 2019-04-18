#include "PanFire.h"
#include "Components/Vector2.h"


PanFire::PanFire(SpriteSheet* sprite) : Fire(sprite)
{
}


PanFire::~PanFire()
{
}

void PanFire::Update(FVector2* pancakePosition, CookingState cookedState)
{

	if (cookedState != CookingState::OnFire)
	{
		canRender = false;
		return;
	}

	Fire::Update(0.5f);	// Clamp the size of fire to .5

	SetAnchoredPosition(pancakePosition->x+100, pancakePosition->y+20);

	canRender = true;

}

void PanFire::Render(SDL_Renderer* renderer)
{

	if ( !canRender ) return;

	Fire::Render(renderer);

}