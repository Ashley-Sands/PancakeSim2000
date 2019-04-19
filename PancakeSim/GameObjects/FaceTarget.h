#pragma once
#include "Components/SpriteAnimator.h"

class SDL_Renderer;
class DistanceTrigger;

enum FaceSide
{
	Left,
	Right
};

class FaceTarget : public SpriteAnimator
{

public:
	FaceTarget(SpriteSheet* sprite);
	~FaceTarget();

	virtual void Begin() override;
	void Update();
	virtual void Render(SDL_Renderer* renderer) override;

	void SetSpriteId(int sid);
	void SetActive(bool act);
	bool GetActive();

private:

	DistanceTrigger* distanceTrigger;

	int spriteId = 0;
	FaceSide currentFaceSide = FaceSide::Left;

	//Gets the left or right position of the face.
	int GetFixedFacePosition_X();

	bool isActive = false;

	float moveLength = 10.0;
	float currentMoveTime = 0;
	bool moveForwards = true;

};

