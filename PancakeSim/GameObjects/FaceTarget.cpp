#include "FaceTarget.h"
#include "Components/SpriteSheet.h"
#include "Components/Vector2.h"
#include "Components/Settings/GameSettings.h"
#include "Components/Time.h"
#include "Components/Debug/Console.h"
#include "Components/DistanceTrigger.h"
#include "Components/Helper.h"

FaceTarget::FaceTarget(SpriteSheet* sprite) : SpriteAnimator(sprite)
{

	distanceTrigger = new DistanceTrigger(this);

}


FaceTarget::~FaceTarget()
{
	delete distanceTrigger;
}

void FaceTarget::Begin()
{
	SpriteAnimator::Begin();
}

void FaceTarget::Update()
{

	if (!isActive) return;

	float currentMovePosition = currentMoveTime / moveLength;

	float yPosition = 150 + ((GameSettings::window_height - 750) * currentMovePosition);

	SetPosition( GetFixedFacePosition_X(), yPosition );

	// Should we change direction?
	if (currentMovePosition > 1.0f && moveForwards) moveForwards = false;
	else if (currentMovePosition < 0.0f && !moveForwards) moveForwards = true;

	currentMoveTime += (moveForwards ? Time::GetDeltaSeconds() : -Time::GetDeltaSeconds());

}

void FaceTarget::Render(SDL_Renderer* renderer)
{

	if (!isActive) return;

	SpriteAnimator::Render(renderer);

}

void FaceTarget::SetSpriteId(int id)
{
	spriteId = id;
	GetSpriteSheet()->GetSpriteRectByID(spriteId, /*out*/ currentSpritePos);
}

void FaceTarget::SetActive(bool act)
{
	isActive = act;

	if (isActive)
		currentFaceSide = (FaceSide)(Helper::Random() % 2);

}

bool FaceTarget::GetActive()
{
	return isActive;
}

int FaceTarget::GetFixedFacePosition_X()
{
	switch (currentFaceSide)
	{
	case FaceSide::Left:
		return -(GetSize()->x * 0.45f);
	case FaceSide::Right:
		return GameSettings::window_width - (GetSize()->x * 0.55f);
	default:
		Console::LogMessage(MessageType::Error, "Can not find fade side :(");
		return -100;
	}
}

DistanceTrigger* FaceTarget::GetTrigger()
{
	return distanceTrigger;
}