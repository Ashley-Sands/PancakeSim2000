#pragma once
#include "SDL.h"

/* SDL Includes (note to self)
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
*/
#include <serial\serial.h>
#include "SerialInterface.h"

class Sprite;
class Time;

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
	void HandleKeyboardEvents();
	void HandleEvents();
	void Clean();

	
	bool Running() { return isRunning; };

private:
	
	// main SDL win, renderer & surface :)
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Surface* mainSurface;

	// Game Components
	Time* time;

	//Inits
	bool InitSerialConnection();
	void InitGameComponents();	// use to inisalize the game compoents that require the main SDL bits

	bool ignoreSerial = true;// false;
	int forceComPort = -1;
	SerialInterface* serial;


	bool isRunning;



//TESTING ONLY
	Sprite* tempcake;
	Sprite* tempPan;
	int f = 0;
};

