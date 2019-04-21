#pragma once

#include "Scene.h"

class Game;
class Sprite;
class SDL_Rect;

class Scene_splash : public Scene
{
public:
	Scene_splash(Game* game);
	~Scene_splash();

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;

private:

	Sprite* sprite_logo;
	SDL_Rect* logoPosition;

	float length = 5;
	float currentPosition;

};

