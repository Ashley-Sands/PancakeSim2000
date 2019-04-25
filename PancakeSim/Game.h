#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

/* SDL Includes (note to self)
#include "SDL_mixer.h"
#include "SDL_image.h"

*/
#include <serial\serial.h>
#include "SerialInterface.h"

class Sprite;
class SpriteSheet;
class SpriteObject;
class Time;
class FryingPan;
class Pancake;
class Fire;
class PanFire;
class InputData;
class Vector2;
class TextTransform;
class FaceTarget;
class Whisk;
class InputData_single;
class Jug;
class Scene;

class Game
{
public:
	Game();
	~Game();

	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Render();
	void Update();
	void HandleSerialEvents();
	void HandleSerialOutput(std::string output);
	void HandleKeyboardEvents(SDL_Event* event);
	void HandleEvents();
	void Clean();

	SDL_Renderer* GetRenderer();
	
	bool Running() { return isRunning; };
	void OnScoreChanged();
private:
	
	// main SDL win, renderer & surface :)
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Surface* mainSurface;

	//Inits
	bool InitSerialConnection();
	void InitGameComponents();	// use to inisalize the game compoents that require the main SDL bits
	
	bool isRunning;


	// serial input/outpit commuication 
	SerialInterface* serial;
	bool ignoreSerial = false; //true;// false;
	int forceComPort = 3;


// Fonts
	TTF_Font* mainFontFace;

/////////////////////////////////////////////////////
// TODO
// I think this is the most part of the main scene!
//
/////////////////////////////////////////////////////

//TESTING ONLY

// UI (BETA)

	TextTransform* UI_scoreLable;
	TextTransform* UI_scoreValue;

	TextTransform* UI_flipsLable;
	TextTransform* UI_flipsCount;

	TextTransform* UI_servedPancakesLable;
	TextTransform* UI_servedPancakesCount;

	TextTransform* UI_happynessLable;
	TextTransform* UI_happynessValue;

// Not UI

	SpriteSheet* tempcake;
	SpriteSheet* tempPan_back;
	SpriteSheet* tempPan_front;

	SpriteSheet* spriteSheet_fire;
	SpriteSheet* spriteSheet_panFire;
	SpriteSheet* spriteSheet_faces;

	SpriteSheet* spriteSheet_jug;
	Sprite* sprite_whisk;

// BETA

	// there needs to be the same amount of pans to pancakes :)
	static const int panCount = 3;
	FryingPan* fryingPans_back[panCount];
	FryingPan* fryingPans_front[panCount];
	Pancake* pancakes[panCount];

	int f = 0;

	Fire* hobFire[panCount];
	PanFire* panFire[panCount];

	float flipForce = 1.0f; //TESTING ONLY

//Faces [BETA]
	static const int faceCount = 4;
	FaceTarget* faceTargets[faceCount];

	bool showFace = false;
	FaceTarget* activeFace;

//BETE INPUT (using pong controller)
	InputData* fryingPans_inputValue[panCount];
	InputData_single* single_inputValue;

	Vector2* fryingPans_lastInput[panCount];	//this can not be a pointer since it needs to be a copy of the last position :)
	Vector2* fryingPans_inputDelta[panCount];

	InputData* fryingPans_keyboardInputValues[panCount];
	InputData_single* single_keyboardInputValue;


	const int maxPanRotation = 40;

	const int hobStartValue = 435;
	const int hobMaxValue = 1023 - hobStartValue;

// jug ( i think that this should be moved into the jug update when i add it )
	Jug* jug;
	int currentPourId = -1; // < 0 = not pouring
	float TMEP_POUR_RATE = 0;

// Whisk
	Whisk* whisk;

//Scenes
	Scene* currentScene;

};

