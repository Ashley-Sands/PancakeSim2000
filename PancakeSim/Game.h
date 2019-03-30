#pragma once
#include "SDL.h"

/* SDL Includes (note to self)
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
*/
#include <serial\serial.h>
#include "SerialInterface.h"

class Game
{
public:
	Game();
	~Game();

	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Render();
	void Update();
	void HandleSerialEvents();
	void HandleKeyboardEvents();
	void HandleEvents();
	void Clean();

	bool InitSerialConnection();
	bool Running() { return isRunning; };

private:
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	
	bool ignoreSerial = true;// false;
	int forceComPort = -1;
	SerialInterface* serial;


	bool isRunning;

	

};

