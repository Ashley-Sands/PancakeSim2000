#include "stdafx.h"
#include "Game.h"
#include "SDL_image.h"

#include <iostream>
//Pancake Sim 2000
#include "GameObjects/Components/Components.h"
#include "GameObjects/GameObjects.h"

//Debuging
#include "GameObjects/Components/Debug/Console.h"

Game::Game()
{
	staticTempCake_sprite = new Sprite();

	tempcake = new SpriteSheet();
	tempPan_back = new SpriteSheet();
	tempPan_front = new SpriteSheet();
	
}

Game::~Game()
{
	delete tempcake;
	delete tempPan_back;
	delete tempPan_front;
	delete staticTempCake_sprite;
	delete staticTempCake;
	
	delete[] &fryingPans_back;
	delete[] &fryingPans_front;
	delete[] &pancakes;

}

bool Game::InitSerialConnection()
{
	if (ignoreSerial)
	{
		Console::LogMessage(MessageType::Warning, "Ignoring Serial inputs (Disabled)");
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
		Console::LogMessage(MessageType::Log, "SDL init success");

		// initialise PNG image files
		if (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
		{
			Console::LogMessage(MessageType::Log, "IMG PNG init success");

			// Create a window
			mainWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			mainSurface = SDL_GetWindowSurface(mainWindow);
			
			// if window succesful..
			if (mainWindow != 0) 
			{
				Console::LogMessage(MessageType::Log, "Window creation success");

				// create renderer
				mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
				SDL_SetRenderDrawBlendMode(mainRenderer, SDL_BLENDMODE_BLEND);

				// if renderer successful...
				if (mainRenderer != 0) {
					Console::LogMessage(MessageType::Log, "Renderer creation success");
					SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
				}
				else 
				{
					Console::LogMessage(MessageType::Error, "renderer failed");
					return false;
				}
			}
			else {
				Console::LogMessage(MessageType::Error, "window failed");
				return false;
			}
		}
		else
		{
			Console::LogMessage(MessageType::Error, "Failed to init PNG images");
		}
	}
	else 
	{
		Console::LogMessage(MessageType::Error, "SDL fail");
		return false;
	}

	isRunning = true;
	Console::LogMessage(MessageType::Log, "SDL init success");

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

	tempPan_back->SetSprite(mainRenderer, "Sprites/pans_back_ss.png");
	tempPan_back->SetSpriteSize(200);

	tempPan_front->SetSprite(mainRenderer, "Sprites/pans_front_ss.png");
	tempPan_front->SetSpriteSize(200);

	// Abit realer.
	for (int i = 0; i < panCount; i++)
	{
		//init pans and pancakes
		fryingPans_back[i] = new FryingPan(tempPan_back);
		fryingPans_back[i]->SetPosition(10 + (210 * i), 350);
		fryingPans_back[i]->SetScale(1.1f, 1.1f);

		fryingPans_front[i] = new FryingPan(tempPan_front);
		fryingPans_front[i]->SetPosition(10 + (210 * i), 350);
		fryingPans_front[i]->SetScale(1.1f, 1.1f);

		pancakes[i] = new Pancake(tempcake);
		pancakes[i]->SetAnchor(TransformAnchor::Center);
		pancakes[i]->SetAnchoredPosition(140 + (213 * i), 250 , pancakes[i]->GetSpriteSheet()->GetSpriteSize()->x, pancakes[i]->GetSpriteSheet()->GetSpriteSize()->y);
		pancakes[i]->SetScale(0.8f, 0.8f);

		//Setup inputs :)
		fryingPans_inputValue[i] = serial->GetPot(i);
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
	
	//staticTempCake->Render(mainRenderer);
	//staticTempCake->SetScale((float)(f % (10 * 50)) / 50.0f, (float)(f % (10 * 50)) / 50.0f);

	for (int i = 0; i < panCount; i++)
	{
		fryingPans_back[i]->Render(mainRenderer);
		pancakes[i]->Render(mainRenderer);
		fryingPans_front[i]->Render(mainRenderer);

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
		fryingPans_back[i]->Update(*fryingPans_inputValue[i] / 1023.0f);// (float)(f % 60) / 60.0f);
		fryingPans_front[i]->Update(*fryingPans_inputValue[i] / 1023.0f);// (float)(f % 60) / 60.0f);

		pancakes[i]->Update( fryingPans_inputDelta[i] / 150.0f, fryingPans_back[i]->GetCurrentSpriteId() );// ((float)(f % 60/*(rand() % 60 + 1)*/) / 60.0f) // (float)(f % (int)(60.0f * flipForce)) / (60.0f * flipForce));



	}
	flipForce = 0;
}

void Game::HandleSerialEvents()
{
	if (serial->connect)
	{
		serial->GetPositions();	// Get and update from the controler.
		
		for (int i = 0; i < panCount; i++)
		{
			fryingPans_inputDelta[i] = *fryingPans_inputValue[i] - fryingPans_lastInput[i];
			fryingPans_lastInput[i]  = *fryingPans_inputValue[i];
		}
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
				if (f <= 55)
					flipForce = 0.25f + ((rand() % 100) / 100.0f);// 0.75;
				
				f += 5;
				if (f >= 60) f = 59;
				
			}
			else if (event.key.keysym.sym == SDLK_s)
			{
				f -= 5;
				if (f < 0)f = 0;
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
	Console::LogMessage(MessageType::Log, "Cleaning SDL");
	SDL_FreeSurface(mainSurface);
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	IMG_Quit();
	SDL_Quit();
}


