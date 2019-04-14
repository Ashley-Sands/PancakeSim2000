#include "Pancake.h"
#include "Components/SpriteSheet.h"
#include "Components/Sprite.h"
#include "Components/Rigidbody.h"
#include "Components/Time.h"
#include "Components/Vector2.h"

// debuging
#include "Components/Debug/Console.h"

#define OUT

Pancake::Pancake(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
	rigidbody = new Rigidbody(this, 0.2f);
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

	spriteSheet->GetSpriteRectByID(spriteID, OUT currentSpritePos);

	//RB bits
	if( GetPosition()->y >= 350 )//TODO: this should really be in the pan bit
	{
		rigidbody->SetVelocity(0.0f, 1.5f * inputValue);
		currentFlip = 0.0f;
		currentFlipForce = (flipForce * inputValue);
	}

	rigidbody->Update();

}

float Pancake::GetFlipPercentage()
{
	// make the flip fast to start and slow down until theres no force left to apply
	currentFlip += (Time::GetDeltaSeconds() * currentFlipForce);
	currentFlipForce -= (counterForce * Time::GetDeltaSeconds());

	if (currentFlipForce < 0.0f) currentFlipForce = 0.0f;

	// prevent the flip going over 100%
	// always keep it within the flipLength 
	while(currentFlip > flipLength)
		currentFlip -= flipLength;

	return 1.0f - (currentFlip / flipLength);		// invert the flip (sprit sheet is backwards :S )
}