#pragma once
#include "Scene.h"
#include "..\GameObjects\Components\Managers\GameManager.h"

class TextTransform;
class SpriteSheet;
class Sprite;
class FryingPan;
class Pancake;
class Fire;
class PanFire;
class FaceTargets;
class Whisk;
class Jug;


class Scene_mainGame :	public Scene
{

public:
	Scene_mainGame(Game* mainGame);
	~Scene_mainGame();

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
	virtual void UpdateUI() override;
private:

// UI

	TextTransform* UI_scoreLable;
	TextTransform* UI_scoreValue;

	TextTransform* UI_flipsLable;
	TextTransform* UI_flipsCount;

	TextTransform* UI_servedPancakesLable;
	TextTransform* UI_servedPancakesCount;

	TextTransform* UI_happynessLable;
	TextTransform* UI_happynessValue;

// sprites and sprite sheets

	SpriteSheet* spriteSheet_pancake;
	SpriteSheet* spriteSheet_pan_back;
	SpriteSheet* spriteSheet_pan_front;

	SpriteSheet* spriteSheet_fire;
	SpriteSheet* spriteSheet_panFire;
	SpriteSheet* spriteSheet_faces;

	SpriteSheet* spriteSheet_jug;
	Sprite* sprite_whisk;				// Removed??

// Objects

	// there needs to be the same amount of pans to pancakes :)
	FryingPan* fryingPans_back[GameManager::panCount];
	FryingPan* fryingPans_front[GameManager::panCount];
	Pancake* pancakes[GameManager::panCount];

	Fire* hobFire[GameManager::panCount];
	PanFire* panFire[GameManager::panCount];

	//Faces
	static const int faceCount = 4;
	FaceTarget* faceTargets[faceCount];

	bool showFace = false;
	FaceTarget* activeFace;

	const int hobStartValue = 435;
	const int hobMaxValue = 1023 - hobStartValue;


	// jug ( i think that this should be moved into the jug update when i add it )
	Jug* jug;
	int currentPourId = -1;

	const float jugPour_buttonUp_Thresshold = 0.5f;
	float justPour_currentButtonUp_Time;

	// Whisk
	Whisk* whisk;
};

