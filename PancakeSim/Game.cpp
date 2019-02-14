#include "stdafx.h"
#include "Game.h"
#include <iostream>

using std::cout;

Game::Game()
{
	
}


Game::~Game()
{
}

bool Game::InitSerialConnection()
{

	serial = new SerialInterface();

	return true;
}
/*
* init - used to initialise and setup SDL
* Return true if everything is successful
*/
bool Game::Init(const char * title, int xpos, int ypos, int width, int height, int flags)
{
	// initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "SDL init success \n";

		// Create a window
		mainWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// if window succesful..
		if (mainWindow != 0) {
			cout << "Window creation success \n";

			// create renderer
			mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);

			// if renderer successful...
			if (mainRenderer != 0) {
				cout << "Renderer creation success \n";
				SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
			}
			else {
				cout << "renderer failed \n";
				return false;
			}
		}
		else {
			cout << "window failed \n";
			return false;
		}

	}
	else {
		cout << "SDL fail \n";
		return false;
	}

	isRunning = true;
	cout << "SDL init success \n";

	InitSerialConnection();

	return true;
}

// render - Process all sprites to be displayed on the main renderer
void Game::Render()
{
	// set background color
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
	
	// clear previous frame
	SDL_RenderClear(mainRenderer);

	// draw to the screen here!
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	//SDL_RenderFillRect(mainRenderer,&playerOnePosition);		// render a rect to screen. (renderer, rect)
	//SDL_RenderFillRect(mainRenderer,&playerTwoPosition);
	
	// render new frame
	SDL_RenderPresent(mainRenderer);
}


// update - Process all variables !in charge of anything to do with rendering
void Game::Update()
{
	
}

void Game::HandleSerialEvents()
{
	if (serial->connect)
	{
		serial->GetPositions();	// Get an update from the controler.
		//playerOnePosition.y = (serial->getPot1() / 1023.0f) * 405;
		//playerTwoPosition.y = (serial->getPot2() / 1023.0f) * 405;
	}
}


// handleEvents - Poll Events and uses switch case to process specific events
void Game::HandleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_KEYDOWN:
			
			if (event.key.keysym.sym == SDLK_w)
			{
				std::cout << "W Pressed\n";
			}
			else if (event.key.keysym.sym == SDLK_s)
			{
				std::cout << "S Pressed\n";

			}
			break;
		default:
			break;
		}

	}
}


// clean - Clean up SDL and close the port
void Game::Clean()
{	
	cout << "Cleaning SDL \n";
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	SDL_Quit();
}


