#pragma once
#include "SDL.h"
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
	void HandleEvents();
	void Clean();

	bool InitSerialConnection();
	bool Running() { return isRunning; };

private:
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SerialInterface* serial;

	bool isRunning;

	

};

