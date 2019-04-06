#pragma once
#include "Transform.h"
#include "SDL.h"

class SDL_Renderer;
class Sprite;
class Time;

class SpriteObject : public Transform
{
public:
	SpriteObject(Sprite* sprite);
	~SpriteObject();

	void virtual Render(SDL_Renderer* renderer);

	Sprite* GetSprite();

protected:
	Sprite* sprite;
};

