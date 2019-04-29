#pragma once
#include "Components/SpriteAnimator.h"
#include "Components/Managers/GameManager.h"
#include <map>

class SpriteSheet;
class Vector2;

class Jug : public SpriteAnimator
{
public:
	Jug(SpriteSheet* sprite);
	~Jug();

	virtual void Begin() override;
	void Update(int rot);

	float Pour();

	void SetPourPosition(int id, int x, int y);
	Vector2* GetPourPosition(int id);			//Gets the pour position at id if valid
	void SetPourPositionId(int id);
	int GetPourPositionId();
	void IdlePourPosition();

private:
	const float max_mixture = 100.0f;
	float currentMixture = 100.0f;

	const float maxPourRate = 10.0f;

	float currentRotation = 0;
	const float minRotation = 5;				// min rotaiton to start pouring
	const float maxRotation = 180;				// max pour rotation
	const float rotationMultiplier = 0.25f;		// rotation position multiplyer

	Vector2* pourPositions[GameManager::panCount + 1];	// 1 pour position for each pan and one for the default location.

	int currentPourPosition = GameManager::panCount;	// Start on the last element in the array since this is our idle position 

};

