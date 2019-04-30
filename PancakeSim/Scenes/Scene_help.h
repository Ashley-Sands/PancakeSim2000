#pragma once
#include "Scene.h"

class Game;
class TextTransform;
class SDL_Rect;
class Sprite;

class Scene_help :	public Scene
{
public:
	Scene_help(Game* game);
	~Scene_help();

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
	virtual void UpdateUI() override {};

private:

	Sprite* sprite_logo;
	SDL_Rect* logoPosition;

	Sprite* sprite_help;
	SDL_Rect* helpPosition;

};

