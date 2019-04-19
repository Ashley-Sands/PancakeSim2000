#include "Pancake.h"
#include "Components/SpriteSheet.h"
#include "Components/Sprite.h"
#include "Components/Rigidbody.h"
#include "Components/Time.h"
#include "Components/Vector2.h"
#include "Components/Managers/GameManager.h"
#include "Components/Settings/GameSettings.h"

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
	SpriteAnimator::Begin();
	startPosition = GetAnchoredPosition()->x;

}

void Pancake::Update(float force, int panSpriteId, int panRotation, float hobValue, float flameSize)	//TODO: added cooking temp.
{

	if (pancakeSize == 0.0f) return;	//Theres no pancake to display

	// Get the current sprite position on the sprite sheet, when being fliped
	SpriteSheet* spriteSheet = GetSpriteSheet();
	int spriteID = 0;

	float offHobOffset = 100.0f * (1 - hobValue);	//TODO: Come on...

	Console::LogMessage(MessageType::Log, "Hob Value: " + std::to_string(hobValue));

	if (GetAnchoredPosition()->x < (startPosition - (GetSize()->x / 2.0f)) || GetAnchoredPosition()->x > (startPosition + (GetSize()->x / 2.0f))) // Pancake can't be chatched // this should be worked out to the size of the pan
	{
		if (GetAnchoredPosition()->y > 500 || GetAnchoredPosition()->x < -150 || GetAnchoredPosition()->x > GameSettings::window_width+150)
		{	
			ServePancake(false);
		}
	} //we're in the pan :)
	else if (GetAnchoredPosition()->y >= 455 - (panSpritePositionMultiplier * panSpriteId) - offHobOffset) //TODO: this should really be in the pan bit
	{ 	//TODO: replace magic numbers throughtout this if statment

		float force_x = 0;
		
		if(abs(panRotation) > 20.0f)		// min rotating to throw pancakes 
			force_x = panRotation / -40.0f;	//I should realy use the force from the accel (insted of the Y delta). TODO: <<

		if (force_y_accum > 0 && force < 0 || panSpriteId > 4 && force_y_accum > 0.0f)
		{
			force = force_y_accum / fc;
			force_y_accum = 0;
			fc = 0;
		}
		else if (force > 0.1)
		{
			force_y_accum += force;
			fc++;
			force = 0;
		}
		else
		{
			force = 0;
			force_y_accum = 0;
			fc = 0;
		}

		if (/*panSpriteId < 4 ||*/ force < minFlipForce || currentCookState == CookingState::Mixture) // can not flip if pan has not roted enought //TODO: improve this so it uses the Accum delta and release when the force stops or goes backwards
		{
			force = 0.0f;
			force_x = 0.0f;
		}
		else if (abs(force_x) < 0.5f)
		{
			force_x = 0.0f;
		}
		else
		{
			force_x *= force;
		}
		

		//RB / flip
		rigidbody->SetVelocity(force_x, 1.5f * force);
		currentFlip = 0.0f;
		currentFlipForce = (flipForce * force);
		
		// correct the pancakes position when in pan
		if (force < minFlipForce)
		{
			float fixed_x_pos = startPosition + ((float)panRotation * 0.85f) - (((panRotation < 0.0f ? -1.0f : 1.0f) * 4.0f) * (3.0f - (float)panSpriteId));
			SetAnchoredPosition(fixed_x_pos, 455 - (panSpritePositionMultiplier * panSpriteId) - offHobOffset);
			spriteID = (spriteSheet->GetTotalSprites() - 1) - floor(panSpriteId / 2.0f);
		}

		currentCookingTime += Time::GetDeltaSeconds() * hobValue * flameSize * (1.2f - GetPancakeSizePercentage()); //TODO: Add cooking temp mutiplyer
		SetCurrentCookingState();

		SetRotation(panRotation);

	}
	else if ( GetPosition()->y >= 310 - offHobOffset && rigidbody->GetVelocity()->y < 0)	//correct position when entering pan
	{
		spriteID = (spriteSheet->GetTotalSprites() - 1) - floor(panSpriteId / 2.0f);
		SetRotation(panRotation);

	}
	else // we're fliping pancakes :D
	{
		spriteID = spriteSheet->GetSpriteIdByPercentage(GetFlipPercentage());
	}

	Console::LogMessage(MessageType::Log, "Pancake Position y: " + std::to_string(GetPosition()->y) +" State: "+ std::to_string(currentCookState) + " Velocity X: "+std::to_string(rigidbody->GetVelocity()->x) );

	spriteSheet->GetSpriteRectByID(spriteID, /*out*/ currentSpritePos, currentSpriteRow);

	rigidbody->Update();

}

void Pancake::PourPancake(float rate)
{

	if (!canPour) return;

	pancakeSize += ( rate * Time::GetDeltaSeconds() );

	if (pancakeSize > maxPancakeSize) pancakeSize = maxPancakeSize;

	SetScale(pancakeSize, pancakeSize);
	currentCookingTime = 0;
	currentCookState = CookingState::Mixture;

	if (pancakeSize > minPancakeSize && rate == 0.0f)
		canPour = false;
	else if (pancakeSize <= 0.1f && rate == 0.0f)
		pancakeSize = 0.0f;

}

float Pancake::GetPancakeSizePercentage()
{
	return (pancakeSize - minPancakeSize) / (maxPancakeSize - minPancakeSize);
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
	{
		currentCookState = CookingState::Mixture;
		currentSpriteRow = 0;
	}
	else if (currentCookingTime < (cookingLength * rawMutiplyer))
	{
		currentCookState = CookingState::Raw;
		currentSpriteRow = 1;
	}
	else if (currentCookingTime > (cookingLength * fireMutiplyer))
	{
		currentCookState = CookingState::OnFire;
		currentSpriteRow = 6;
	}
	else if (currentCookingTime > (cookingLength * burntMutiplyer))
	{
		currentCookState = CookingState::Burnt;
		currentSpriteRow = 4;
	}
	else
	{
		currentCookState = CookingState::Perfect;
		currentSpriteRow = 3;
	}
}

bool Pancake::CanPour()
{
	return canPour;
}

void Pancake::ServePancake(bool hit)
{
	//Work out the happyness
	float happyness = 0.0f;

	if (!hit)
		happyness = -0.15;
	else
		happyness =  GetCookStateHappyness();

	// Reset the pancake
	currentCookState = CookingState::None;
	currentCookingTime = 0;
	pancakeSize = 0;
	SetScale(0, 0);
	canPour = true;
	SetPosition(startPosition, 1000);	//it needs to be set below its start position x so update can correct it :|


	GameManager::GetInstance().AddServedPancake(happyness);

}

float Pancake::GetCookStateHappyness()
{

	switch (currentCookState)
	{
		case CookingState::None: 
		case CookingState::Mixture:
									return 0;
		case CookingState::Raw:		return 0.25f;
		case CookingState::Perfect: return 1.0f;
		case CookingState::Burnt:	return 0.25f;
		case CookingState::OnFire:	return -1000.0f;			//The lesson here is to not play with fire. :D
		default:					return 0.0f;
	}

}