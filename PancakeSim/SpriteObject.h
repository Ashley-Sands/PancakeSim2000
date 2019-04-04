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

	void virtual Update(Time* time);		//TODO: I think this should just be called render and there should be a seprate update function :)
	void virtual Render(SDL_Renderer* renderer);

private:
	Sprite* sprite;
};

