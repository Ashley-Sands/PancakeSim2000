#include "stdafx.h"
#include "Game.h"
#include "SDL_image.h"

#include <iostream>

//Pancake Sim 2000
#include "GameObjects/GameObjects.h"
#include "GameObjects/Components/Components.h"
#include "GameObjects/Components/InputDataTypes/InputData.h"
#include "GameObjects/Components/InputDataTypes/InputData_single.h"
#include "GameObjects/Components/UI/UI.h"
#include "GameObjects/Components/Managers/GameManager.h"
#include "GameObjects/Components/Settings/GameSettings.h"

#include "Scenes/scenes.h"
#include "Scenes/Scene_mainGame.h"
//Debuging
#include "GameObjects/Components/Debug/Console.h"

Game::Game()
{
	// construct the scenes without initalizing :)
	scenes["splash"] = new Scene_splash(this);
	scenes["main"]= new Scene_mainGame(this);

	backgroundColor = new SDL_Color();

}

Game::~Game()
{

	delete[] &fryingPans_lastInput;
	delete[] &fryingPans_inputDelta;
	delete[] &fryingPans_keyboardInputValues;

	delete single_keyboardInputValue;

	delete UI_FPS;
	
	if (ignoreSerial)
		delete[] &fryingPans_inputValue;

	scenes.clear();
	delete currentScene;

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

	if (serial && serial->connect)	// Drop the fps so the controller can keep up and we so we have a smooth frame rate
		Time::SetFPS(20);

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

		// Initialise TTF fonts
		if (TTF_Init() == 0)
		{

			Console::LogMessage(MessageType::Log, "TTF font init success");

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
			Console::LogMessage(MessageType::Error, "Failed to init TTF fonts");
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

	//Load successful, set this to the active game. 
	GameManager::GetInstance().SetActiveGame(this);

	//Setup inputs for all the pans :)
	for (int i = 0; i < GameManager::panCount; i++)
	{
		
		fryingPans_inputDelta[i] = new Vector2();
		fryingPans_lastInput[i] = new Vector2();
		fryingPans_keyboardInputValues[i] = new InputData();

		fryingPans_inputValue[i] = ( ignoreSerial ? fryingPans_keyboardInputValues[i] : serial->GetPot(i) );
	}

	single_keyboardInputValue = new InputData_single();
	single_inputValue = ( ignoreSerial ? single_keyboardInputValue : serial->GetSinglePot() );		// Get single object input values

	

	// UI
	mainFontFace = TTF_OpenFont("Fonts/ARIALN.ttf", 60);

	UI_FPS = new TextTransform(mainFontFace);
	UI_FPS->SetText("0 FPS");
	UI_FPS->SetPosition(15, GameSettings::window_height-40);
	UI_FPS->SetScale(0.5f, 0.5f);

	GameManager::GetInstance().onScoreChanged = &Game::OnScoreChanged;

	// Load the first scene.
	LoadScene("splash");

}

// render - Process all sprites to be displayed on the main renderer
void Game::Render()
{
	// set background color
	SDL_SetRenderDrawColor(mainRenderer, backgroundColor->r, backgroundColor->g, backgroundColor->b, 255);

	// clear previous frame
	SDL_RenderClear(mainRenderer);
		
	// Scene
	currentScene->Render();

	// Rendered in all scenes
	if (showFPS)
		UI_FPS->Render(mainRenderer);

	// render new frame
	//SDL_UpdateWindowSurface(mainWindow);
	SDL_RenderPresent(mainRenderer);

}


// update - Process all variables !in charge of anything to do with rendering
void Game::Update()
{
	// skip the update to help prevent any cray deltas affter the scene has been loaded or when the game starts :)
	if (skipUpdate)
	{
		skipUpdate = false;
		return;
	}

	flipForce = 0;

	// Scenes
	currentScene->Update();

	// Elements that are in all scenes
	if(showFPS)
		UI_FPS->SetText(std::to_string( (1.0f/Time::GetDeltaSeconds()) ) + " FPS");

}

void Game::OnScoreChanged()
{

	currentScene->UpdateUI();

}


void Game::LoadScene(std::string name)
{	//TODO: it would be cool if i unloaded (but its not really worth it for a game of this size)

	if (scenes.count(name) == 0)
	{
		Console::LogMessage(MessageType::Error, "Scene " + name + "not found");
		return;
	}

	//Check if the scene has been initalized.
	if (!scenes[name]->HasInitalized())
		scenes[name]->Init();
	

	currentScene = scenes[name];
	skipUpdate = true;			// skip the update to prevent a crazzy delta on the first update affter the scene has been loaded

}

void Game::HandleSerialEvents()
{
	if (serial->connect)
	{
		serial->GetPositions();	// Get and update from the controler.
		
		for (int i = 0; i < GameManager::panCount; i++)
		{
			// Limit the pans rotation to max pan Rotation
			if (fryingPans_inputValue[i]->GetGyroAxis()->x < -maxPanRotation)
				fryingPans_inputValue[i]->GetGyroAxis()->x = -maxPanRotation;
			else if (fryingPans_inputValue[i]->GetGyroAxis()->x > maxPanRotation)
				fryingPans_inputValue[i]->GetGyroAxis()->x = maxPanRotation;

			// Invert the inputValue Y since its the opersit to what we want :)
			fryingPans_inputDelta[i]->x = fryingPans_inputValue[i]->GetGyroAxis()->x - fryingPans_lastInput[i]->x;
			fryingPans_inputDelta[i]->y = fryingPans_inputValue[i]->GetGyroAxis()->y - fryingPans_lastInput[i]->y;

			fryingPans_lastInput[i]->x  = fryingPans_inputValue[i]->GetGyroAxis()->x;
			fryingPans_lastInput[i]->y  = fryingPans_inputValue[i]->GetGyroAxis()->y;

			fryingPans_inputValue[i]->SetHobValue( fryingPans_inputValue[i]->GetHobValue() -  hobStartValue );
		}
	}
}

void Game::HandleSerialOutput(std::string output)
{

	if (!ignoreSerial && serial != nullptr && !serial->connect) return;

	serial->Send(output);
}

// handleEvents - Poll Events and uses switch case to process specific events
void Game::HandleKeyboardEvents(SDL_Event* event)
{
	
	switch (event->type) {
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_KEYDOWN:
			
			if (event->key.keysym.sym == SDLK_w)
			{
				if (f <= 55)
					flipForce = 0.25f + ((rand() % 100) / 100.0f);// 0.75;
				
				f += 5;
				if (f >= 60) f = 59;
				
				fryingPans_keyboardInputValues[1]->GetGyroAxis()->y += 100;
				if (fryingPans_keyboardInputValues[1]->GetGyroAxis()->y > 1023)
					fryingPans_keyboardInputValues[1]->GetGyroAxis()->y = 1023;


			}
			else if (event->key.keysym.sym == SDLK_s)
			{
				f -= 5;
				if (f < 0)f = 0;

				fryingPans_keyboardInputValues[1]->GetGyroAxis()->y -= 100;
				if (fryingPans_keyboardInputValues[1]->GetGyroAxis()->y < 0)
					fryingPans_keyboardInputValues[1]->GetGyroAxis()->y = 0;

			}

			break;
		case SDL_KEYUP:

			break;
		default:
			break;
	}

	
}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// loop all input events and send the event to keyboard events only if serial is not in use
		// we need to do the DSL_QUIT check here so we can exit the game via 'X'
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}
		else if (event.type == SDL_KEYDOWN)		//Normalize the MPU devices
		{
			if (event.key.keysym.sym == SDLK_n)
			{
				if (!ignoreSerial && serial != nullptr && serial->connect)
				{
					serial->Send("N");
					Console::LogMessage(MessageType::Log, "Normalizing Devices");
				}
				else
				{
					Console::LogMessage(MessageType::Error, "Unable to Normalize devices. Serial is unavailable");
				}
			}
			else if (event.key.keysym.sym == SDLK_p)
			{
				showFPS = !showFPS;
			}
		}
		
	//	if (ignoreSerial || serial == nullptr || !serial->connect)
	//	{
			HandleKeyboardEvents(&event);
	//	}
	}


	if (!ignoreSerial && serial != nullptr && serial->connect)
		HandleSerialEvents();

}

void Game::SetBackgroundColor(int r, int g, int b)
{

	backgroundColor->r = r;
	backgroundColor->g = g;
	backgroundColor->b = b;

}

SDL_Renderer* Game::GetRenderer()
{
	return mainRenderer;
}

TTF_Font * Game::GetMainFontFace()
{
	return mainFontFace;
}

// clean - Clean up SDL and close the port
void Game::Clean()
{	
	Console::LogMessage(MessageType::Log, "Cleaning SDL");

	if (serial && serial->connect)
		serial->Close();

	SDL_FreeSurface(mainSurface);
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


