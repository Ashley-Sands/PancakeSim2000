#pragma once
#include "Transform.h"
#include "SDL.h"

class SDL_Renderer;
class Sprite;
class Time;

class SpriteObject : Transform
{
public:
	SpriteObject(Sprite* sprite);
	~SpriteObject();

	void virtual Update(Time* time, SDL_Renderer* renderer);

private:
	Sprite* sprite;
};

