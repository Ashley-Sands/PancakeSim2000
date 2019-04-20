#include "Whisk.h"
#include "Components/Sprite.h"
#include "Components/Time.h"

Whisk::Whisk(Sprite* sprite) : SpriteObject(sprite)
{
}


Whisk::~Whisk()
{
}

void Whisk::Upadate(bool isWhisking)
{
	
	if (isWhisking)
	{

		currentRotation += whiskSpeed * rotationDirection * Time::GetDeltaSeconds();
		float scale = 0.85f + ((currentRotation + maxRotation) / (maxRotation*2.0f) * 0.2f);
		SetScale(scale, scale);
		// reverse direct
		if (abs(currentRotation) >= maxRotation)
		{
			currentRotation = maxRotation * rotationDirection;
			rotationDirection *= -1;
		}
	}
	else
	{
		currentRotation = 35;
	}

	SetRotation(currentRotation);

}
