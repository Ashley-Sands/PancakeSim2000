#include "SpriteAnimator.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include "Vector2.h"


SpriteAnimator::SpriteAnimator(SpriteSheet* sprite) : SpriteObject(sprite)
{
	currentSpritePos = new SDL_Rect();
}


SpriteAnimator::~SpriteAnimator()
{
	delete currentSpritePos;
}

SpriteSheet* SpriteAnimator::GetSpriteSheet()
{
	return (SpriteSheet*)sprite;
}

void SpriteAnimator::Render(SDL_Renderer* renderer)
{

	// Get the position to render the sprite
	SDL_Rect* destPos = GetRectScaled();

	sprite->RenderSprite(renderer, destPos, GetRotation(), currentSpritePos);

}