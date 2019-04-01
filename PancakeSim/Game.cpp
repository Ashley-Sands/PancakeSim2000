#include "stdafx.h"
#include "Game.h"
#include "SDL_image.h"

#include <iostream>

//TESTING (ATM)
#include "sprite.h";


using std::cout;

Game::Game()
{
	tempcake = new Sprite();
	
}


Game::~Game()
{
	delete tempcake;
}

bool Game::InitSerialConnection()
{
	if (ignoreSerial)
	{
		cout << "Ignoring Serial inputs (Disabled)";
		return false;			
	}
	else if (forceComPort < 0)
	{
		serial = new SerialInterface();
	}
	else
	{
		serial = new SerialInterface(forceComPort);
	}

	return true;
}
/*
* init - used to initialise and setup SDL
* Return true if everything is successful
*/
bool Game::Init(const char * title, int xpos, int ypos, int width, int height, int flags)
{
	// initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		cout << "SDL init success \n";

		// initialise PNG image files
		if (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
		{
			cout << "IMG PNG init success \n";

			// Create a window
			mainWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			mainSurface = SDL_GetWindowSurface(mainWindow);
			
			// if window succesful..
			if (mainWindow != 0) 
			{
				cout << "Window creation success \n";

				// create renderer
				mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
				SDL_SetRenderDrawBlendMode(mainRenderer, SDL_BLENDMODE_BLEND);

				// if renderer successful...
				if (mainRenderer != 0) {
					cout << "Renderer creation success \n";
					SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
				}
				else 
				{
					cout << "renderer failed \n";
					return false;
				}
			}
			else {
				cout << "window failed \n";
				return false;
			}
		}
		else
		{
			cout << "Failed to init PNG images \n";
		}
	}
	else 
	{
		cout << "SDL fail \n";
		return false;
	}

	isRunning = true;
	cout << "SDL init success \n";

	InitSerialConnection();
	InitGameComponents();


	return true;
}

void Game::InitGameComponents()
{
	//tempcake->SetSprite("Sprites/TempCake_000.png", mainSurface->format);
	tempcake->SetSprite(mainRenderer, "Sprites/TempCake_000.png");
}

// render - Process all sprites to be displayed on the main renderer
void Game::Render()
{
	// set background color
	
	
	// clear previous frame
	SDL_RenderClear(mainRenderer);

	// draw to the screen here!
	//SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	//SDL_RenderFillRect(mainRenderer,&playerOnePosition);		// render a rect to screen. (renderer, rect)
	//SDL_RenderFillRect(mainRenderer,&playerTwoPosition);
	
	//SDL_BlitSurface(tempcake->GetSprite(), NULL, mainSurface, NULL);
	SDL_Rect sRect;
	sRect.x = f*0.2f; sRect.y = 0;
	sRect.w = 100; sRect.h = 100;
	
	//SDL_BlitScaled(tempcake->GetSprite(), NULL, mainSurface, &sRect);
	//SDL_SetSurfaceBlendMode(mainSurface, SDL_BLENDMODE_BLEND);
	//SDL_SetSurfaceAlphaMod(mainSurface, 0);
	SDL_RenderCopy(mainRenderer, tempcake->GetSprite(), NULL, &sRect);
	// render new frame
	SDL_RenderPresent(mainRenderer);
	//SDL_UpdateWindowSurface(mainWindow);
	f++;
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
void Game::HandleKeyboardEvents()
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

void Game::HandleEvents()
{
	// use controler inputs if avable.
	if (!ignoreSerial && serial != nullptr && serial->connect)
		HandleSerialEvents();
	else
		HandleKeyboardEvents();

}

// clean - Clean up SDL and close the port
void Game::Clean()
{	
	cout << "Cleaning SDL \n";
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	SDL_Quit();
}


