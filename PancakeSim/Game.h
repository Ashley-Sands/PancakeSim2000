#pragma once
#include <map>
#include "SDL.h"
#include "SDL_ttf.h"

/* SDL Includes (note to self)
#include "SDL_mixer.h"
#include "SDL_image.h"

*/
#include <serial\serial.h>
#include "SerialInterface.h"
//#include "GameObjects/Components/Managers/GameManager.h"

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

	void SetBackgroundColor(int r, int g, int b);
	SDL_Renderer* GetRenderer();
	TTF_Font* GetMainFontFace();

	bool Running() { return isRunning; };
	void OnScoreChanged();

	void LoadScene(std::string name);

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


	SDL_Color* backgroundColor;
// Fonts
	TTF_Font* mainFontFace;
//UI
	bool showFPS;
	TextTransform* UI_FPS;



// BETA & Testing
	int f = 0;
	float flipForce = 1.0f; //TESTING ONLY

//INPUTS
public:
	static const int panCount = 3;
	//The inputs are public since they are heverly shared with the scene class!
	// TODO: move to input handler
	InputData* fryingPans_inputValue[panCount];
	InputData_single* single_inputValue;
	Vector2* fryingPans_inputDelta[panCount];

private:

	bool skipUpdate = false;

	Vector2* fryingPans_lastInput[panCount];	//this can not be a pointer since it needs to be a copy of the last position :)

	InputData* fryingPans_keyboardInputValues[panCount];
	InputData_single* single_keyboardInputValue;

	const int maxPanRotation = 40;
	const int hobStartValue = 435;

//Scenes
	Scene* currentScene;
	std::map<std::string, Scene*> scenes;

	bool displayHelp = false;
	Scene* helpScene;
};

