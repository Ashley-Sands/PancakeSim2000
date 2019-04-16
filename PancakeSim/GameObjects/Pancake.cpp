#include "Pancake.h"
#include "Components/SpriteSheet.h"
#include "Components/Sprite.h"
#include "Components/Rigidbody.h"
#include "Components/Time.h"
#include "Components/Vector2.h"
#include "Components/Managers/GameManager.h"

// debuging
#include "Components/Debug/Console.h"

Pancake::Pancake(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
	rigidbody = new Rigidbody(this, 0.2f);
	rigidbody->SetVelocity(0.0f, 0.0f);
}


Pancake::~Pancake()
{
	delete rigidbody;
}

void Pancake::Begin()
{
	startPosition = GetPosition()->x;
}

void Pancake::Update(float force, int panSpriteId, int panRotation)	//TODO: added cooking temp.
{

	// Get the current sprite position on the sprite sheet, when being fliped
	SpriteSheet* spriteSheet = GetSpriteSheet();
	int spriteID = 0;

	
	//we're in the pan :)
	//TODO: replace magic numbers throughtout this if statment
	if (GetPosition()->y >= 365 - (5 * panSpriteId))//TODO: this should really be in the pan bit
	{

		if (panSpriteId < 4 || currentCookState == CookingState::Mixture) force = 0.0f;	// can not flip if pan has not roted enought
		
		//RB / flip
		rigidbody->SetVelocity(0.0f, 1.5f * force);
		currentFlip = 0.0f;
		currentFlipForce = (flipForce * force);
		
		// correct the pancakes position when in pan
		SetPosition(GetPosition()->x, 365 - (5 * panSpriteId));
		spriteID = (spriteSheet->GetTotalSprites()-1) - floor(panSpriteId / 2.0f);

		currentCookingTime += Time::GetDeltaSeconds(); //TODO: Add cooking temp mutiplyer
		SetCurrentCookingState();

		SetRotation(panRotation);

	}
	else if ( GetPosition()->y >= 310 && rigidbody->GetVelocity()->y < 0)	//correct position when entering pan
	{
		spriteID = (spriteSheet->GetTotalSprites() - 1) - floor(panSpriteId / 2.0f);
		SetRotation(panRotation);
	}
	else // we're fliping pancakes :D
	{
		spriteID = spriteSheet->GetSpriteIdByPercentage(GetFlipPercentage());
	}

	Console::LogMessage(MessageType::Log, "Pancake Position y: " + std::to_string(GetPosition()->y) +" State: "+ std::to_string(currentCookState) );

	spriteSheet->GetSpriteRectByID(spriteID, /*out*/ currentSpritePos);

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
	while (currentFlip > flipLength)
	{
		GameManager::GetInstance().AddFlip();
		currentFlip -= flipLength;
	}

	return 1.0f - (currentFlip / flipLength);		// invert the flip (sprit sheet is backwards :S )
}

CookingState Pancake::GetCurrentCookingState()
{
	return currentCookState;
}

void Pancake::SetCurrentCookingState()
{

	if (currentCookingTime < (cookingLength * mixtureMutiplyer))
		currentCookState = CookingState::Mixture;
	else if (currentCookingTime < (cookingLength * rawMutiplyer))
		currentCookState = CookingState::Raw;
	else if (currentCookingTime > (cookingLength * fireMutiplyer))
		currentCookState = CookingState::Fire;
	else if (currentCookingTime > (cookingLength * burntMutiplyer))
		currentCookState = CookingState::Burnt;
	else
		currentCookState = CookingState::Perfect;
}