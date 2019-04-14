#include "stdafx.h"
#include "Game.h"
#include "SDL_image.h"

#include <iostream>
//Pancake Sim 2000
#include "GameObjects/Components/Components.h"
#include "GameObjects/GameObjects.h"

using std::cout;

Game::Game()
{
	staticTempCake_sprite = new Sprite();

	tempcake = new SpriteSheet();
	tempPan = new SpriteSheet();
	
}

Game::~Game()
{
	delete tempcake;
	delete tempPan;
	delete staticTempCake_sprite;
	delete staticTempCake;
	
	delete[] &fryingPans;
	delete[] &pancakes;

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
	
	staticTempCake_sprite->SetSprite(mainRenderer, "Sprites/TempCake_000.png");
	staticTempCake = new SpriteObject(staticTempCake_sprite);

	staticTempCake->SetPosition(-200, -200);

	tempcake->SetSprite(mainRenderer, "Sprites/TEMPCAKE_SS.png");
	tempcake->SetSpriteSize(200);

	tempPan->SetSprite(mainRenderer, "Sprites/PAN_SS.png");
	tempPan->SetSpriteSize(200);


	// Abit realer.
	for (int i = 0; i < panCount; i++)
	{
		//init pans and pancakes
		fryingPans[i] = new FryingPan(tempPan);
		fryingPans[i]->SetPosition(10 + (210 * i), 350);

		pancakes[i] = new Pancake(tempcake);
		pancakes[i]->SetPosition(20 + (220 * i), 0);
		pancakes[i]->SetScale(0.8f, 0.8f);

	}

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
	
	staticTempCake->Render(mainRenderer);
	staticTempCake->SetScale((float)(f % (10 * 50)) / 50.0f, (float)(f % (10 * 50)) / 50.0f);

	for (int i = 0; i < panCount; i++)
	{
		fryingPans[i]->Render(mainRenderer);
		pancakes[i]->Render(mainRenderer);
	}

	// render new frame
	SDL_RenderPresent(mainRenderer);
	//SDL_UpdateWindowSurface(mainWindow);

}


// update - Process all variables !in charge of anything to do with rendering
void Game::Update()
{
	//f++;
	for (int i = 0; i < panCount; i++)
	{
		fryingPans[i]->Update((float)(f % 60) / 60.0f);
		pancakes[i]->Update( ((float)(f % (rand() % 60 + 1)) / 30.0f) );// (float)(f % (int)(60.0f * flipForce)) / (60.0f * flipForce));
	}
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
				f += 5;
				if (f > 30) f = 30;
			}
			else if (event.key.keysym.sym == SDLK_s)
			{
				f -= 5;
				if (f < 0)f = 0;
			}
			else if (event.key.keysym.sym == SDLK_2)
			{
				flipForce = 1;
			}
			else if (event.key.keysym.sym == SDLK_EQUALS)
			{
				flipForce += 0.5f;
			}
			else if (event.key.keysym.sym == SDLK_MINUS)
			{
				flipForce -= 0.5f;
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
	SDL_FreeSurface(mainSurface);
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	IMG_Quit();
	SDL_Quit();
}


