#include "Pancake.h"
#include "Components/SpriteSheet.h"
#include "Components/Sprite.h"
#include "Components/Rigidbody.h"
#include "Components/Time.h"
#include "Components/Vector2.h"

Pancake::Pancake(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
	rigidbody = new Rigidbody(this, new FVector2(0.0f, -1.5f));
}


Pancake::~Pancake()
{
	delete rigidbody;
}

void Pancake::Update(float inputValue)
{

	// Get the current sprite position on the sprite sheet
	SpriteSheet* spriteSheet = GetSpriteSheet();
	int spriteID = spriteSheet->GetSpriteIdByPercentage(GetFlipPercentage());//inputValue);

	spriteSheet->GetSpriteRectByID(spriteID, currentSpritePos);

	//RB bits
	if( GetPosition()->y >= 200 )//TODO: this should really be in the pan bit
	{
		rigidbody->SetVelocity(0.0f, 4.0f); 
		currentFlip = 0.0f;
		flipForce = 4;
	}

	rigidbody->Update();

}

float Pancake::GetFlipPercentage()
{
	currentFlip += (Time::GetDeltaSeconds() * flipForce);
	flipForce -= (counterForce * Time::GetDeltaSeconds());

	if (flipForce < 0.0f) flipForce = 0.0f;
	if (currentFlip > flipLength) currentFlip -= flipLength;

	return currentFlip / flipLength;
}