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

	void virtual Update(Time* time, SDL_Renderer* renderer);		//TODO: I think this should just be called render and there should be a seprate update function :)

private:
	Sprite* sprite;
};

