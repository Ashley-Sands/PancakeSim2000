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
	rigidbody = new Rigidbody(this, default_mass);
	rigidbody->SetVelocity(0.0f, 0.0f);

	outOfBounds = new FVector2(150, 500);

}


Pancake::~Pancake()
{
	delete rigidbody;
	delete outOfBounds;
}

void Pancake::Begin()
{
	SpriteAnimator::Begin();
	startPosition = GetAnchoredPosition()->x;

}

void Pancake::Update(float force, int panSpriteId, int panRotation, float onHobValue, float flameSize)
{

	if (pancakeSize == 0.0f) return;	//Theres no pancake to display

	rigidbody->Update();

	// Get the current sprite position on the sprite sheet, when being fliped
	SpriteSheet* spriteSheet = GetSpriteSheet();
	int spriteID = 0;

	float offHobOffset = 100.0f * (1 - onHobValue);	//TODO: Come on...

	// assume we are not in the pan
	inPan = false;

	Console::LogMessage(MessageType::Log, "Hob Value: " + std::to_string(onHobValue));

	if (GetAnchoredPosition()->x < (startPosition - (GetSize()->x / 2.0f)) || GetAnchoredPosition()->x > (startPosition + (GetSize()->x / 2.0f))) // Pancake can't be chatched // this should be worked out to the size of the pan
	{

		if (GetAnchoredPosition()->y > outOfBounds->y || GetAnchoredPosition()->x < -outOfBounds->x || GetAnchoredPosition()->x > GameSettings::window_width + outOfBounds->x)
		{	
			ServePancake(false);
		}
	} //we're in the pan :)
	else if (GetAnchoredPosition()->y >= panBottomPosition - (panBottom_spriteIdOffset * panSpriteId) - offHobOffset) //TODO: make into its own function :/
	{ 	//TODO: replace magic numbers throughtout this if statment

		inPan = true;
		float force_x = 0;
		
		//TODO: sort this mess out
		if(abs(panRotation) > 20.0f)		// min rotating to throw pancakes 
			force_x = -panRotation / 40.0f;	//I should realy use the force from the accel (insted of the Y delta). TODO: << 



		if (force_y_accum > 0 && force < 0 || panSpriteId > 4 && force_y_accum > 0.0f)
		{
			force = (force_y_accum + force) / force_y_frameCount;
			force_y_accum = 0;
			force_y_frameCount = 0;

		}
		else if (force > 0 && panSpriteId <= 4)
		{
			force_y_accum += force;
			force_y_frameCount++;
			force = 0;
		}
		else
		{
			force = 0;
			force_y_accum = 0;
			force_y_frameCount = 0;
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
		
		// correct the pancakes position when in pan
		if (force < minFlipForce)
		{
			float fixed_x_pos = startPosition + ((float)panRotation * 0.85f) - (((panRotation < 0.0f ? -1.0f : 1.0f) * 4.0f) * (3.0f - (float)panSpriteId));
			SetAnchoredPosition(fixed_x_pos, panBottomPosition - (panBottom_spriteIdOffset * panSpriteId) - offHobOffset);
			spriteID = (spriteSheet->GetTotalSprites() - 1) - floor(panSpriteId / 2.0f);
			rigidbody->SetVelocity(force_x, 0);
		}
		else //RB / flip
		{
			rigidbody->SetVelocity(force_x, 1.5f * force);
			currentFlip = 0.0f;
			currentFlipForce = (flipForce * force);
		}

		currentCookingTime += Time::GetDeltaSeconds() * onHobValue * flameSize * (2.0f - GetPancakeSizePercentage());
		SetCurrentCookingState();

		SetRotation(panRotation);

	}	// TODO: improve the position at which we correct the position
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
	{
		canPour = false;
		float newMass = (pancakeSize / maxPancakeSize) * default_mass;
		rigidbody->SetMass(newMass);
	}
	else if (pancakeSize <= minPancakeSize && rate == 0.0f)
	{
		pancakeSize = 0.0f;
	}
}

void Pancake::SetPancakeSize(float size)
{
	pancakeSize = size;
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

void Pancake::SetCurrentCookingState(CookingState state)
{
	currentCookState = state;

	switch (state)
	{
		case CookingState::Raw:		currentCookingTime = 0;									break;
		case CookingState::Mixture: currentCookingTime = (cookingLength * rawMutiplyer);	break;
		case CookingState::Perfect: currentCookingTime =  cookingLength;					break;
		case CookingState::Burnt:	currentCookingTime = (cookingLength * burntMutiplyer);	break;
		case CookingState::OnFire:	currentCookingTime = (cookingLength * fireMutiplyer);	break;
	}

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
		GameManager::GetInstance().SoundAlarm(false);					//TODO: give me a real home :)
	}
	else if (currentCookingTime > (cookingLength * burntMutiplyer))
	{
		currentCookState = CookingState::Burnt;
		currentSpriteRow = 4;
	}
	else
	{
		currentCookState = CookingState::Perfect;
		currentSpriteRow = 2;
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

	GameManager::GetInstance().AddServedPancake(happyness, pancakeSize);
	GameManager::GetInstance().SoundAlarm(true);

	// Reset the pancake
	currentCookState = CookingState::None;
	currentCookingTime = 0;
	pancakeSize = 0;
	SetScale(0, 0);
	canPour = true;
	SetPosition(startPosition, 1000);	//it needs to be set below its start position x so update can correct it :|

}

bool Pancake::IsInPan()
{
	return inPan;
}

void Pancake::SetPanBottom(float position, float spriteOffset)
{

	panBottomPosition = position;
	panBottom_spriteIdOffset = spriteOffset;

}

void Pancake::SetBounds(float x_bounds, float y_bounds)
{
	outOfBounds->SetVector(x_bounds, y_bounds);
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