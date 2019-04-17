#include "PanFire.h"
#include "Components/Vector2.h"


PanFire::PanFire(SpriteSheet* sprite) : Fire(sprite)
{
}


PanFire::~PanFire()
{
}

void PanFire::Update(FVector2* pancakePosition)
{

	Fire::Update(1);	// Clamp the size of fire to one

	SetPosition(pancakePosition->x, pancakePosition->y);

}