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
class InputData;
class Vector2;

class Game
{
public:
	Game();
	Game(Time* time);
	~Game();

	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Render();
	void Update();
	void HandleSerialEvents();
	void HandleKeyboardEvents(SDL_Event* event);
	void HandleEvents();
	void Clean();

	
	bool Running() { return isRunning; };

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



	SpriteSheet* tempcake;
	SpriteSheet* tempPan_back;
	SpriteSheet* tempPan_front;
	SpriteSheet* spriteSheet_fire;

// BETA

	// there needs to be the same amount of pans to pancakes :)
	static const int panCount = 3;
	FryingPan* fryingPans_back[panCount];
	FryingPan* fryingPans_front[panCount];
	Pancake* pancakes[panCount];

	int f = 0;

	Fire* hobFire[panCount];

	float flipForce = 1.0f; //TESTING ONLY

//BETE INPUT (using pong controller)
	InputData* fryingPans_inputValue[panCount];

	Vector2* fryingPans_lastInput[panCount];	//this can not be a pointer since it needs to be a copy of the last position :)
	Vector2* fryingPans_inputDelta[panCount];

	InputData* fryingPans_keyboardInputValues[panCount];

	const int maxPanRotation = 40;

	const int hobStartValue = 435;
	const int hobMaxValue = 1023 - hobStartValue;
};

