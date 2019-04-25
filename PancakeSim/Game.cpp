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

#include "Scenes/scenes.h"

//Debuging
#include "GameObjects/Components/Debug/Console.h"

Game::Game()
{
	// TODO Rename
	tempcake = new SpriteSheet();
	tempPan_back = new SpriteSheet();
	tempPan_front = new SpriteSheet();
	
	spriteSheet_fire = new SpriteSheet();
	spriteSheet_panFire = new SpriteSheet();

	spriteSheet_faces = new SpriteSheet();

	spriteSheet_jug = new SpriteSheet();
	sprite_whisk = new Sprite();

	currentScene = new Scene_splash(this);

}

Game::~Game()
{
	delete tempcake;
	delete tempPan_back;
	delete tempPan_front;
	
	delete[] &fryingPans_back;
	delete[] &fryingPans_front;
	delete[] &pancakes;

	delete[] &fryingPans_lastInput;
	delete[] &fryingPans_inputDelta;
	delete[] &fryingPans_keyboardInputValues;

	delete single_keyboardInputValue;

	delete spriteSheet_fire;
	delete spriteSheet_panFire;
	delete spriteSheet_faces;
	
	delete spriteSheet_jug;
	delete sprite_whisk;

	delete whisk;
	delete jug;

	delete UI_scoreLable;
	delete UI_scoreValue;
	delete UI_flipsLable;
	delete UI_flipsCount;

	delete[] faceTargets;

	if (ignoreSerial)
		delete[] &fryingPans_inputValue;

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

	Console::LogMessage(MessageType::Log, "LOADING SPRITES...\n");

	tempcake->SetSprite(mainRenderer, "Sprites/TEMPCAKE_all.png");
	tempcake->SetSpriteSize(200, 200);

	tempPan_back->SetSprite(mainRenderer, "Sprites/pans_back_ss.png");
	tempPan_back->SetSpriteSize(200);

	tempPan_front->SetSprite(mainRenderer, "Sprites/pans_front_ss.png");
	tempPan_front->SetSpriteSize(200);

	spriteSheet_fire->SetSprite(mainRenderer, "Sprites/Fire_SS.png");
	spriteSheet_fire->SetSpriteSize(200);

	spriteSheet_panFire->SetSprite(mainRenderer, "Sprites/PanFire_SS.png");
	spriteSheet_panFire->SetSpriteSize(200);

	spriteSheet_faces->SetSprite(mainRenderer, "Sprites/Faces.png");
	spriteSheet_faces->SetSpriteSize(200);

	spriteSheet_jug->SetSprite(mainRenderer, "Sprites/Jug_SS.png");
	spriteSheet_jug->SetSpriteSize(200);
	
	sprite_whisk->SetSprite(mainRenderer, "Sprites/Whisk.png");

	// Abit realer.
	for (int i = 0; i < panCount; i++)
	{
		//init pans and pancakes
		fryingPans_back[i] = new FryingPan(tempPan_back);
		fryingPans_back[i]->SetPosition(10 + (210 * i), 350);
		fryingPans_back[i]->SetScale(1.1f, 1.1f);

		fryingPans_back[i]->Begin();

		fryingPans_front[i] = new FryingPan(tempPan_front);
		fryingPans_front[i]->SetPosition(10 + (210 * i), 350);
		fryingPans_front[i]->SetScale(1.1f, 1.1f);

		fryingPans_front[i]->Begin();


		pancakes[i] = new Pancake(tempcake);
		pancakes[i]->SetAnchor(TransformAnchor::Center);
		pancakes[i]->SetAnchoredPosition(40 + (213 * i), 550);		// set the position of the pancakes well below the pan so it can be corrected to the correct Y position :) (Yeee-haaa)
		pancakes[i]->SetScale(0.8f, 0.8f);

		pancakes[i]->Begin();

		hobFire[i] = new Fire(spriteSheet_fire);
		hobFire[i]->SetAnchor(TransformAnchor::Center);
		hobFire[i]->SetScale(1.05f, 1.05f);
		hobFire[i]->SetAnchoredPosition(120 + (210 * i), 470);

		hobFire[i]->Begin();

		panFire[i] = new PanFire(spriteSheet_panFire);
		panFire[i]->SetAnchor(TransformAnchor::Center);
		panFire[i]->SetAnchoredPosition(120 + (210 * i), 470); //??
		panFire[i]->SetInvervalLength(0.175f);
		panFire[i]->Begin();

		//Setup inputs :)
		fryingPans_inputDelta[i] = new Vector2();
		fryingPans_lastInput[i] = new Vector2();
		fryingPans_keyboardInputValues[i] = new InputData();

		fryingPans_inputValue[i] = ( ignoreSerial ? fryingPans_keyboardInputValues[i] : serial->GetPot(i) );
	}

	single_keyboardInputValue = new InputData_single();
	single_inputValue = ( ignoreSerial ? single_keyboardInputValue : serial->GetSinglePot() );		// Get single object input values


	// Jug
	jug = new Jug(spriteSheet_jug);
	jug->SetPosition(80, 120);
	jug->Begin();

	// Whisk
	whisk = new Whisk(sprite_whisk);
	whisk->SetPosition(165, 100);
	whisk->Begin();

	// Setup UI.
	mainFontFace = TTF_OpenFont("Fonts/ARIALN.ttf", 60);

	UI_scoreLable = new TextTransform(mainFontFace);
	UI_scoreLable->SetText("Score");
	UI_scoreLable->SetPosition( 80, 15 );
	UI_scoreLable->SetScale( 0.5f, 0.5f );

	UI_scoreValue = new TextTransform(mainFontFace);
	UI_scoreValue->SetText("0");
	UI_scoreValue->SetPosition( 155, 15 );
	UI_scoreValue->SetScale( 0.5f, 0.5f );

	UI_flipsLable = new TextTransform(mainFontFace);
	UI_flipsLable->SetText("Flips");
	UI_flipsLable->SetPosition( 230, 15 );
	UI_flipsLable->SetScale( 0.5f, 0.5f );

	UI_flipsCount = new TextTransform(mainFontFace);
	UI_flipsCount->SetText("0");
	UI_flipsCount->SetPosition(300, 15);
	UI_flipsCount->SetScale(0.5f, 0.5f);


	UI_servedPancakesLable = new TextTransform(mainFontFace);
	UI_servedPancakesLable->SetText("Servered");
	UI_servedPancakesLable->SetPosition(360, 15);
	UI_servedPancakesLable->SetScale(0.5f, 0.5f);

	UI_servedPancakesCount = new TextTransform(mainFontFace);
	UI_servedPancakesCount->SetText("0");
	UI_servedPancakesCount->SetPosition(475, 15);
	UI_servedPancakesCount->SetScale(0.5f, 0.5f);

	UI_happynessLable = new TextTransform(mainFontFace);
	UI_happynessLable->SetText("Happyness");
	UI_happynessLable->SetPosition(535, 15);
	UI_happynessLable->SetScale(0.5f, 0.5f);

	UI_happynessValue = new TextTransform(mainFontFace);
	UI_happynessValue->SetText("100%");
	UI_happynessValue->SetPosition(690, 15);
	UI_happynessValue->SetScale(0.5f, 0.5f);


	GameManager::GetInstance().onScoreChanged = &Game::OnScoreChanged;

	//Setup Face Targets
	for (int i = 0; i < faceCount; i++)
	{
		faceTargets[i] = new FaceTarget(spriteSheet_faces);
		faceTargets[i]->SetAnchor(TransformAnchor::Center);
		faceTargets[i]->SetSpriteId(i);

		faceTargets[i]->Begin();
	}

	//////////////////////
	// Scene
	///////////////////////
	currentScene->Init();

}

// render - Process all sprites to be displayed on the main renderer
void Game::Render()
{
	// set background color
	
	SDL_SetRenderDrawColor(mainRenderer, 155, 100, 75, 255);

	// clear previous frame
	SDL_RenderClear(mainRenderer);

	// draw to the screen here!
	SDL_Rect tempCooker_rect;

	tempCooker_rect.h = 200;
	tempCooker_rect.w = 650;
	tempCooker_rect.x = 0;
	tempCooker_rect.y = 425;

	SDL_SetRenderDrawColor(mainRenderer, 155, 155, 155, 255);
	SDL_RenderFillRect(mainRenderer, &tempCooker_rect);	

	tempCooker_rect.h = 150;
	tempCooker_rect.w = 150;
	tempCooker_rect.x = 400;
	tempCooker_rect.y = 175;

	SDL_SetRenderDrawColor(mainRenderer, 0, 55, 255, 255);
	SDL_RenderFillRect(mainRenderer, &tempCooker_rect);
	//SDL_RenderFillRect(mainRenderer,&playerTwoPosition);
	
	//staticTempCake->Render(mainRenderer);
	//staticTempCake->SetScale((float)(f % (10 * 50)) / 50.0f, (float)(f % (10 * 50)) / 50.0f);

	for (int i = 0; i < panCount; i++)
	{
		hobFire[i]->Render(mainRenderer);
		fryingPans_back[i]->Render(mainRenderer);
		pancakes[i]->Render(mainRenderer);
		panFire[i]->Render(mainRenderer);
		fryingPans_front[i]->Render(mainRenderer);

	}

	// Jug and whisk
	whisk->Render(mainRenderer);
	jug->Render(mainRenderer);


	UI_scoreLable->Render(mainRenderer);
	UI_scoreValue->Render(mainRenderer);
	UI_flipsLable->Render(mainRenderer);
	UI_flipsCount->Render(mainRenderer);
	UI_servedPancakesLable->Render(mainRenderer);
	UI_servedPancakesCount->Render(mainRenderer);
	UI_happynessLable->Render(mainRenderer);
	UI_happynessValue->Render(mainRenderer);

	// render faces
	for (int i = 0; i < faceCount; i++)
	{
		faceTargets[i]->Render(mainRenderer);
	}

	// render new frame
	//SDL_UpdateWindowSurface(mainWindow);

	currentScene->Render();

	SDL_RenderPresent(mainRenderer);

}


// update - Process all variables !in charge of anything to do with rendering
void Game::Update()
{

	for (int i = 0; i < panCount; i++)
	{
		fryingPans_back[i]->Update(fryingPans_inputValue[i]->GetGyroAxis()->y / -35.0f, fryingPans_inputValue[i]->GetHobValue() / (float)hobMaxValue);
		fryingPans_front[i]->Update(fryingPans_inputValue[i]->GetGyroAxis()->y / -35.0f, fryingPans_inputValue[i]->GetHobValue() / (float)hobMaxValue);

		fryingPans_back[i]->SetRotation(fryingPans_inputValue[i]->GetGyroAxis()->x);
		fryingPans_front[i]->SetRotation(fryingPans_inputValue[i]->GetGyroAxis()->x);

		hobFire[i]->Update(fryingPans_inputValue[i]->GetHobFire() / 1023.0f);

		pancakes[i]->Update( fryingPans_inputDelta[i]->y / -20.0f,
							 fryingPans_back[i]->GetCurrentSpriteId(), 
						     fryingPans_inputValue[i]->GetGyroAxis()->x, 
							 ( (fryingPans_inputValue[i]->GetHobValue() / (float)hobMaxValue) ),
							 hobFire[i]->GetFlameSize()
						   );

		panFire[i]->Update( pancakes[i]->GetPosition(), pancakes[i]->GetCurrentCookingState() );

		if (showFace == false && activeFace == nullptr)
		{
			showFace = pancakes[i]->GetCurrentCookingState() >= CookingState::Perfect;
		}

		//Check for pancake and face collision
		if (showFace && activeFace != nullptr)
			if (activeFace->GetTrigger()->Trigger(pancakes[i]))
			{
				pancakes[i]->ServePancake(true);
				
				if (activeFace != nullptr)
					activeFace->SetActive(false);
			}
		// select pancake id to pour
		if (currentPourId == -1 && pancakes[i]->CanPour())
		{
			currentPourId = i;
		}
		else if (currentPourId == i && TMEP_POUR_RATE > 0) //TODO: REMOVED TEMP
		{
			pancakes[i]->PourPancake(jug->Pour() * TMEP_POUR_RATE); //TODO: REMOVED TEMP
		}
		else if (currentPourId == i && TMEP_POUR_RATE == 0) //TODO: Remove. This just fixed porPancake not ending, just while jug->pour is being worked on :)
		{
			pancakes[i]->PourPancake(0); 
		}

		

	//	pancakes[i]->SetScale(1.0f - ((f % 60) / 60.0f), 1.0f - ((f % 60) / 60.0f));
	//	pancakes[i]->SetAnchoredPosition(140 + (213 * i), p);

	}

	//Jug and Whisk
	jug->Update();
	whisk->Upadate(single_inputValue->IsWhisking());

	// if we where pouring a pancake but we can no longer pour we have finished pouring
	// since a pancake can not be poured to if its size is > 0 and the pour rate <= 0
	if ( currentPourId > -1 && !pancakes[currentPourId]->CanPour() ) 
		currentPourId = -1;

	if (showFace && activeFace == nullptr)
	{	// Set a random active face

		int randFace = Helper::Random() % faceCount; // TODO: Make more random :/
		activeFace = faceTargets[randFace];
		activeFace->SetActive(true);
	}
	else if (showFace && activeFace != nullptr && !activeFace->GetActive())
	{
		showFace = false;
		activeFace = nullptr;
	}
	
	if (activeFace != nullptr)
	{
		activeFace->Update();
	}


	flipForce = 0;


	/////////////////////////
	// Scenes
	////////////////////////

	currentScene->Update();
}

void Game::OnScoreChanged()
{

	UI_flipsCount->SetText( std::to_string(GameManager::GetInstance().GetTotalFlips()) );
	UI_scoreValue->SetText( std::to_string(GameManager::GetInstance().GetTotalScore()) );
	UI_servedPancakesCount->SetText( std::to_string(GameManager::GetInstance().GetTotalServedPancakes()) );
	UI_happynessValue->SetText( std::to_string( ceil( GameManager::GetInstance().GetHappyness() * 100.0f ) ) + "%" );

}

void Game::HandleSerialEvents()
{
	if (serial->connect)
	{
		serial->GetPositions();	// Get and update from the controler.
		
		for (int i = 0; i < panCount; i++)
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

			fryingPans_inputValue[i]->SetHobValue( fryingPans_inputValue[i]->GetHobValue() -  hobStartValue );	//Todo.
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

				TMEP_POUR_RATE = 1.0f;

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

			TMEP_POUR_RATE = 0;

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
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)		//Normalize the MPU devices
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
		//else if (ignoreSerial || serial == nullptr || !serial->connect)
		//{
			HandleKeyboardEvents(&event);
		//}
	}


	if (!ignoreSerial && serial != nullptr && serial->connect)
		HandleSerialEvents();

}

SDL_Renderer* Game::GetRenderer()
{
	return mainRenderer;
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


