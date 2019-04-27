#pragma once

#include "Scene.h"

class Game;
class Sprite;
class SDL_Rect;
class TextTransform;
class SpriteSheet;
class Pancake;
class FryingPan;

class Scene_splash : public Scene
{
public:
	Scene_splash(Game* game);
	~Scene_splash();

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
	virtual void UpdateUI() override {};	// not implermented in the splash scene 

private:

	Sprite* sprite_logo;
	SDL_Rect* logoPosition;
	TextTransform* UI_continueText;

	SpriteSheet* spriteSheet_pancake;
	SpriteSheet* spriteSheet_pan_front;
	SpriteSheet* spriteSheet_pan_back;

	const int panInputID = 1; //

	FryingPan* fryingPan_front;
	FryingPan* fryingPan_back;

	Pancake* pancake;

	float length = 5;
	float currentPosition;

};

