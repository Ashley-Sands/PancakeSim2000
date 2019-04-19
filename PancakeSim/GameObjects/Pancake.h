#pragma once
#include "Components/SpriteAnimator.h"
#include "stdio.h"


class Rigidbody;

enum CookingState {
	None    = 0,
	Mixture = 1,
	Raw     = 2,
	Perfect = 3,
	Burnt   = 4,
	OnFire  = 5
};

class Pancake : public SpriteAnimator
{
public:

	Pancake(SpriteSheet* sprite);
	~Pancake();

	virtual void Begin() override;
	void Update(float force, int panSpriteId, int panRotation, float hobValue, float flameSize);

	void PourPancake(float rate);

	CookingState GetCurrentCookingState();

	bool CanPour();

	void ServePancake(bool hit);

private:
	
	Rigidbody* rigidbody;

	float startPosition;

	const float panSpritePositionMultiplier = 6.0f;

	float GetFlipPercentage();	// Get the flip playback position in %

	float flipLength = 1.5;			//@ fliForce = 1
	float currentFlip = 0;
	
	const float flipForce = 4;
	float currentFlipForce = 0;
	float counterForce = 2.2f;

	const float minFlipForce = 0.5f;

	int currentSpriteRow = 0;

// Pancake size
	float pancakeSize = 0.0f;
	const float maxPancakeSize = 0.75f;
	const float minPancakeSize = 0.2f;
	bool canPour = true;

// Cooking
	const float cookingLength = 25.0f;		// the perfect cooking leght, in seconds
	float currentCookingTime = 0.0f;

	CookingState currentCookState = CookingState::None;
	void SetCurrentCookingState();
	
	float GetCookStateHappyness();

	// Pancakes cooking states mutiplyers (cookingLength * mutiplyer)
	const float mixtureMutiplyer = 0.15f;		// Unflipable, any time below this the pancake is still considered batter.
	const float rawMutiplyer = 0.75f;			// Unedable, any time below this the pancake is considered raw
	const float burntMutiplyer = 1.25f;			// Burnt, any time affter this the pancake is considered burnt
	const float fireMutiplyer = 1.65f;			// any time above this triggers the fire alarm, call the fire bargade!


};

