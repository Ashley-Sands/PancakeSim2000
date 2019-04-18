#include "FaceTarget.h"
#include "Components/SpriteSheet.h"
#include "Components/Vector2.h"
#include "Components/Settings/GameSettings.h"
#include "Components/Time.h"
#include "Components/Debug/Console.h"

FaceTarget::FaceTarget(SpriteSheet* sprite) : SpriteAnimator(sprite)
{
}


FaceTarget::~FaceTarget()
{
}

void FaceTarget::Begin()
{
	SpriteAnimator::Begin();
}

void FaceTarget::Update()
{

	if (!isActive) return;

	float currentMovePosition = currentMoveTime / moveLength;

	float yPosition = 200 + ((GameSettings::window_height - 400) * currentMovePosition);

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
}

int FaceTarget::GetFixedFacePosition_X()
{
	switch (currentFaceSide)
	{
	case FaceSide::Left:
		return 0;
	case FaceSide::Right:
		return GameSettings::window_width - (GetSize()->x / 2.0f);
	default:
		Console::LogMessage(MessageType::Error, "Can not find fade side :(");
		return -100;
	}
}
