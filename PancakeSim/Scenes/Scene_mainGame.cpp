#include "Scene_mainGame.h"
#include "../game.h"
#include "../GameObjects/GameObjects.h"
#include "../GameObjects/Components/Components.h"
#include "../GameObjects/Components/UI/UI.h"
#include "../GameObjects/Components/Debug/Console.h"

#include "../GameObjects/Components/InputDataTypes/InputData.h"
#include "../GameObjects/Components/InputDataTypes/InputData_single.h"


Scene_mainGame::Scene_mainGame(Game* mainGame) : Scene(mainGame)
{

	spriteSheet_pancake = new SpriteSheet();
	spriteSheet_pan_back = new SpriteSheet();
	spriteSheet_pan_front = new SpriteSheet();

	spriteSheet_fire = new SpriteSheet();
	spriteSheet_panFire = new SpriteSheet();

	spriteSheet_faces = new SpriteSheet();

	spriteSheet_jug = new SpriteSheet();
	sprite_whisk = new Sprite();

}


Scene_mainGame::~Scene_mainGame()
{

	delete spriteSheet_pancake;
	delete spriteSheet_pan_back;
	delete spriteSheet_pan_front;

	delete[] &fryingPans_back;
	delete[] &fryingPans_front;
	delete[] &pancakes;

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

}

void Scene_mainGame::Init()
{

	game->SetBackgroundColor(210, 105, 30);
	Console::LogMessage(MessageType::Log, "LOADING SPRITES...\n");

	spriteSheet_pancake->SetSprite(game->GetRenderer(), "Sprites/TEMPCAKE_all.png");
	spriteSheet_pancake->SetSpriteSize(200, 200);

	spriteSheet_pan_back->SetSprite(game->GetRenderer(), "Sprites/pans_back_ss.png");
	spriteSheet_pan_back->SetSpriteSize(200);

	spriteSheet_pan_front->SetSprite(game->GetRenderer(), "Sprites/pans_front_ss.png");
	spriteSheet_pan_front->SetSpriteSize(200);

	spriteSheet_fire->SetSprite(game->GetRenderer(), "Sprites/Fire_SS.png");
	spriteSheet_fire->SetSpriteSize(200);

	spriteSheet_panFire->SetSprite(game->GetRenderer(), "Sprites/PanFire_SS.png");
	spriteSheet_panFire->SetSpriteSize(200);

	spriteSheet_faces->SetSprite(game->GetRenderer(), "Sprites/Faces.png");
	spriteSheet_faces->SetSpriteSize(200);

	spriteSheet_jug->SetSprite(game->GetRenderer(), "Sprites/Jug_SS.png");
	spriteSheet_jug->SetSpriteSize(200);

	sprite_whisk->SetSprite(game->GetRenderer(), "Sprites/Whisk.png");


	// Setup the frying pans pancakes, fire ect, once for each pan :)
	for (int i = 0; i < GameManager::panCount; i++)
	{
		//init pans and pancakes
		fryingPans_back[i] = new FryingPan(spriteSheet_pan_back);
		fryingPans_back[i]->SetPosition(80 + (260 * i), 500);
		fryingPans_back[i]->SetScale(1.1f, 1.1f);

		fryingPans_back[i]->Begin();

		fryingPans_front[i] = new FryingPan(spriteSheet_pan_front);
		fryingPans_front[i]->SetPosition(80 + (260 * i), 500);
		fryingPans_front[i]->SetScale(1.1f, 1.1f);
		fryingPans_front[i]->SetPanBottom_LocalOffset(105);

		fryingPans_front[i]->Begin();


		pancakes[i] = new Pancake(spriteSheet_pancake);
		pancakes[i]->SetAnchor(TransformAnchor::Center);
		pancakes[i]->SetAnchoredPosition(110 + (263 * i), 900);		// set the position of the pancakes well below the pan so it can be corrected to the correct Y position :) (Yeee-haaa)
		pancakes[i]->SetScale(0.8f, 0.8f);
		pancakes[i]->SetPanBottom(fryingPans_front[i]->GetPanBottom(), 6);

		pancakes[i]->Begin();

		hobFire[i] = new Fire(spriteSheet_fire);
		hobFire[i]->SetAnchor(TransformAnchor::Center);
		hobFire[i]->SetScale(1.05f, 1.05f);
		hobFire[i]->SetAnchoredPosition(190 + (260 * i), 625);

		hobFire[i]->Begin();

		panFire[i] = new PanFire(spriteSheet_panFire);
		panFire[i]->SetAnchor(TransformAnchor::Center);
		panFire[i]->SetAnchoredPosition(190 + (260 * i), 590); //??
		panFire[i]->SetInvervalLength(0.175f);
		panFire[i]->Begin();

	}

	// Jug
	jug = new Jug(spriteSheet_jug);
	jug->SetScale(0.8f, 0.8f);
	jug->SetPosition(820, 530);

	jug->Begin();

	// Whisk
	whisk = new Whisk(sprite_whisk);
	whisk->SetPosition(820, 530);
	whisk->Begin();

	//Setup Face Targets
	for (int i = 0; i < faceCount; i++)
	{
		faceTargets[i] = new FaceTarget(spriteSheet_faces);
		faceTargets[i]->SetAnchor(TransformAnchor::Center);
		faceTargets[i]->SetSpriteId(i);

		faceTargets[i]->Begin();
	}

	// Setup UI.
	UI_scoreLable = new TextTransform(game->GetMainFontFace());
	UI_scoreLable->SetText("Score");
	UI_scoreLable->SetPosition(80, 15);
	UI_scoreLable->SetScale(0.5f, 0.5f);

	UI_scoreValue = new TextTransform(game->GetMainFontFace());
	UI_scoreValue->SetText("0");
	UI_scoreValue->SetPosition(155, 15);
	UI_scoreValue->SetScale(0.5f, 0.5f);

	UI_flipsLable = new TextTransform(game->GetMainFontFace());
	UI_flipsLable->SetText("Flips");
	UI_flipsLable->SetPosition(230, 15);
	UI_flipsLable->SetScale(0.5f, 0.5f);

	UI_flipsCount = new TextTransform(game->GetMainFontFace());
	UI_flipsCount->SetText("0");
	UI_flipsCount->SetPosition(300, 15);
	UI_flipsCount->SetScale(0.5f, 0.5f);


	UI_servedPancakesLable = new TextTransform(game->GetMainFontFace());
	UI_servedPancakesLable->SetText("Servered");
	UI_servedPancakesLable->SetPosition(360, 15);
	UI_servedPancakesLable->SetScale(0.5f, 0.5f);

	UI_servedPancakesCount = new TextTransform(game->GetMainFontFace());
	UI_servedPancakesCount->SetText("0");
	UI_servedPancakesCount->SetPosition(475, 15);
	UI_servedPancakesCount->SetScale(0.5f, 0.5f);

	UI_happynessLable = new TextTransform(game->GetMainFontFace());
	UI_happynessLable->SetText("Happyness");
	UI_happynessLable->SetPosition(535, 15);
	UI_happynessLable->SetScale(0.5f, 0.5f);

	UI_happynessValue = new TextTransform(game->GetMainFontFace());
	UI_happynessValue->SetText("100%");
	UI_happynessValue->SetPosition(690, 15);
	UI_happynessValue->SetScale(0.5f, 0.5f);

	initalized = true;

}

void Scene_mainGame::Render()
{

	SDL_Renderer* mainRenderer = game->GetRenderer();
	// draw to the screen here!
	SDL_Rect tempCooker_rect;

	tempCooker_rect.h = 220;
	tempCooker_rect.w = 1000;
	tempCooker_rect.x = 0;
	tempCooker_rect.y = 580;

	SDL_SetRenderDrawColor(mainRenderer, 155, 155, 155, 255);
	SDL_RenderFillRect(mainRenderer, &tempCooker_rect);

	// my poor attampt of a window...
	tempCooker_rect.h = 150;
	tempCooker_rect.w = 150;
	tempCooker_rect.x = 400;
	tempCooker_rect.y = 275;
	// ...ok its a blue square
	SDL_SetRenderDrawColor(mainRenderer, 0, 55, 255, 255);
	SDL_RenderFillRect(mainRenderer, &tempCooker_rect);

	// render all of our pans, pancakes, fire ect...
	for (int i = 0; i < GameManager::panCount; i++)
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

	// render faces
	for (int i = 0; i < faceCount; i++)
	{
		faceTargets[i]->Render(mainRenderer);
	}

	// UI
	UI_scoreLable->Render(mainRenderer);
	UI_scoreValue->Render(mainRenderer);
	UI_flipsLable->Render(mainRenderer);
	UI_flipsCount->Render(mainRenderer);
	UI_servedPancakesLable->Render(mainRenderer);
	UI_servedPancakesCount->Render(mainRenderer);
	UI_happynessLable->Render(mainRenderer);
	UI_happynessValue->Render(mainRenderer);

}

void Scene_mainGame::Update()
{

	for (int i = 0; i < GameManager::panCount; i++)
	{
		fryingPans_back[i]->Update(game->fryingPans_inputValue[i]->GetGyroAxis()->y / -35.0f, game->fryingPans_inputValue[i]->GetHobValue() / (float)hobMaxValue);
		fryingPans_front[i]->Update(game->fryingPans_inputValue[i]->GetGyroAxis()->y / -35.0f, game->fryingPans_inputValue[i]->GetHobValue() / (float)hobMaxValue);

		//TODO: move rotation into Update
		fryingPans_back[i]->SetRotation(game->fryingPans_inputValue[i]->GetGyroAxis()->x);
		fryingPans_front[i]->SetRotation(game->fryingPans_inputValue[i]->GetGyroAxis()->x);

		hobFire[i]->Update(game->fryingPans_inputValue[i]->GetHobFire() / 1023.0f);

		pancakes[i]->Update(game->fryingPans_inputDelta[i]->y / -20.0f,
			fryingPans_back[i]->GetCurrentSpriteId(),
			game->fryingPans_inputValue[i]->GetGyroAxis()->x,
			((game->fryingPans_inputValue[i]->GetHobValue() / (float)hobMaxValue)),
			hobFire[i]->GetFlameSize()
		);

		panFire[i]->Update(pancakes[i]->GetPosition(), pancakes[i]->GetCurrentCookingState());

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
		else if (currentPourId == i)
		{
			pancakes[i]->PourPancake(jug->Pour());
		}

	}

	//Jug and Whisk
	jug->Update(game->single_inputValue->GetPourRotation());
	whisk->Upadate(game->single_inputValue->IsWhisking());

	// if we where pouring a pancake but we can no longer pour we have finished pouring
	// since a pancake can not be poured to if its size is > 0 and the pour rate <= 0
	if (currentPourId > -1 && !pancakes[currentPourId]->CanPour())
		currentPourId = -1;

	if (showFace && activeFace == nullptr)
	{	// Set a random active face

		int randFace = Helper::Random() % faceCount;
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

}

void Scene_mainGame::UpdateUI()
{
	UI_flipsCount->SetText(std::to_string(GameManager::GetInstance().GetTotalFlips()));
	UI_scoreValue->SetText("£" + std::to_string(GameManager::GetInstance().GetTotalScore()));
	UI_servedPancakesCount->SetText(std::to_string(GameManager::GetInstance().GetTotalServedPancakes()));
	UI_happynessValue->SetText(std::to_string(ceil(GameManager::GetInstance().GetHappyness() * 100.0f)) + "%");
}