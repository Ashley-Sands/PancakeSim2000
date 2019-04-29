#include "Jug.h"
#include "Components/SpriteSheet.h"
#include "Components/Time.h"
#include "Components/Helper.h"
#include "Components/Debug/Console.h"
#include "Components/Vector2.h"

Jug::Jug(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
}


Jug::~Jug()
{
	delete[] &pourPositions;
}

void Jug::Begin()
{
	SpriteAnimator::Begin();
}

void Jug::Update(int rotation)
{

	currentRotation = Helper::Clamp(-maxRotation, 10, rotation);

	SetPosition( GetPourPosition( currentPourPosition ) );
	SetRotation( currentRotation * rotationMultiplier );


	// Get the correct sprite for the amount of mixture we have :P
	int currentSpriteId = GetSpriteSheet()->GetSpriteIdByPercentage( (1.0f-(currentMixture / max_mixture)) );
	GetSpriteSheet()->GetSpriteRectByID(currentSpriteId, currentSpritePos);
}

float Jug::Pour()
{
	// can not pour if we have no mixture of if we're in the idle position.
	if (currentMixture <= 0.0f || currentPourPosition >= GameManager::panCount) return 0;

	float pourRate = 0;
	float rotation = abs( Helper::Clamp(-maxRotation, 0, currentRotation) );

	if(rotation > minRotation)
		pourRate = ( maxPourRate * (rotation / maxRotation) ) * Time::GetDeltaSeconds();

	if (pourRate > currentMixture) pourRate = currentMixture;

	currentMixture -= pourRate;

	if (currentMixture < 0.0f)
		currentMixture = 0;

	return pourRate;

}

void Jug::SetPourPosition(int id, int x, int y)
{

	if (id < 0 || id > GameManager::panCount)	
		Console::LogMessage(MessageType::Error, "Invalid pour position ID: " + std::to_string(id));

	else if (pourPositions[id] == nullptr)		
		pourPositions[id] = new Vector2(x, y);

	else										
		pourPositions[id]->SetVector(x, y);

}

Vector2* Jug::GetPourPosition(int id)
{
	
	if (id < 0 || id > GameManager::panCount)	//its > pancount because there a default position and all the pans
	{
		Console::LogMessage(MessageType::Error, "Invalid pour position ID: "+std::to_string(id) );
		return nullptr;
	}
	else if (pourPositions[id] == nullptr)
	{
		Console::LogMessage(MessageType::Error, "Pour position at ID: " + std::to_string(id) + " has not been set");
		return nullptr;
	}
	else
	{
		return pourPositions[id];
	}

}

void Jug::SetPourPosition(int id)
{
	if (id < 0 || id > GameManager::panCount)	//its > pancount because there a default position and all the pans
	{
		Console::LogMessage(MessageType::Error, "Invalid pour position ID: " + std::to_string(id));
		IdlePourPosition();
		return;
	}

	currentPourPosition = id;

}

void Jug::IdlePourPosition()
{
	currentPourPosition = GameManager::panCount;			// the idle position should be the last
}