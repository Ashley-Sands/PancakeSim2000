#include "Pancake.h"
#include "Components/SpriteSheet.h"
#include "Components/Sprite.h"
#include "Components/Rigidbody.h"
#include "Components/Time.h"
#include "Components/Vector2.h"

Pancake::Pancake(SpriteSheet* sprite, Time* time) : SpriteAnimator(sprite)
{
	rigidbody = new Rigidbody(time, this, new FVector2(0.0f, 1.5f));
}


Pancake::~Pancake()
{
}

void Pancake::Update(float inputValue)
{
	SpriteSheet* spriteSheet = GetSpriteSheet();
	int spriteID = spriteSheet->GetSpriteIdByPercentage(inputValue);

	spriteSheet->GetSpriteRectByID(spriteID, currentSpritePos);

	rigidbody->Update();

}