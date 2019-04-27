#include "scene_splash.h"
#include "..\GameObjects\Components\Components.h"
#include "..\Game.h"
#include "..\GameObjects\Components\Managers\GameManager.h"
#include "..\GameObjects\Components\Helper.h"
#include "..\GameObjects\Components\UI\TextTransform.h"
#include "..\GameObjects\GameObjects.h"
#include "..\GameObjects\Components\InputDataTypes\InputData.h"

Scene_splash::Scene_splash(Game* game) : Scene(game)
{
	sprite_logo = new Sprite();
	logoPosition = new SDL_Rect();

	spriteSheet_pancake = new SpriteSheet();
	spriteSheet_pan_front = new SpriteSheet();
	spriteSheet_pan_back = new SpriteSheet();

}


Scene_splash::~Scene_splash()
{

	delete sprite_logo;
	delete logoPosition;
	delete spriteSheet_pancake;
	delete spriteSheet_pan_front;
	delete spriteSheet_pan_back;
	delete fryingPan_front;
	delete fryingPan_front;
	delete pancake;

}

void Scene_splash::Init()
{
	
	// Logo
	sprite_logo->SetSprite(game->GetRenderer(), "Sprites/SimPancake_2000.png");

	logoPosition->w = sprite_logo->GetSpriteSize()->x / 2;
	logoPosition->h = sprite_logo->GetSpriteSize()->y / 2;

	Helper::CenterRectToScreen( /*out*/ logoPosition);
	logoPosition->y = 50;

	// Text
	UI_continueText = new TextTransform(game->GetMainFontFace());
	UI_continueText->SetText("Flip A Pancake To Continue");
	UI_continueText->SetScale(0.5f, 0.5f);
	UI_continueText->SetPosition(250, 250);

	// Pan and pancake sprites
	spriteSheet_pancake->SetSprite(game->GetRenderer(), "Sprites/TEMPCAKE_all.png");
	spriteSheet_pancake->SetSpriteSize(200, 200);

	spriteSheet_pan_back->SetSprite(game->GetRenderer(), "Sprites/pans_back_ss.png");
	spriteSheet_pan_back->SetSpriteSize(200);

	spriteSheet_pan_front->SetSprite(game->GetRenderer(), "Sprites/pans_front_ss.png");
	spriteSheet_pan_front->SetSpriteSize(200);

	// Frying Pan
	fryingPan_back = new FryingPan(spriteSheet_pan_back);
	fryingPan_back->SetAnchor(TransformAnchor::Center);
	fryingPan_back->SetScale(1.1f, 1.1f);
	fryingPan_back->SetAnchoredPosition((GameSettings::window_width / 2.0f) - 100.0f, 350);

	fryingPan_back->Begin();

	fryingPan_front = new FryingPan(spriteSheet_pan_front);
	fryingPan_front->SetAnchor(TransformAnchor::Center);
	fryingPan_front->SetScale(1.1f, 1.1f);
	fryingPan_front->SetAnchoredPosition((GameSettings::window_width / 2.0f) - 100.0f, 350);

	fryingPan_front->Begin();

	// Pancake
	pancake = new Pancake(spriteSheet_pancake);
	pancake->SetAnchor(TransformAnchor::Center);
	pancake->SetScale(0.8f, 0.8f);
	pancake->SetAnchoredPosition((GameSettings::window_width / 2.0f) - 60, 150);

	pancake->Begin();
	// Set up a pan for a pratics flip :)
	pancake->SetPancakeSize(0.75);
	pancake->SetCurrentCookingState(CookingState::Perfect);

	//Game
	game->SetBackgroundColor(50, 50, 50);
	game->HandleSerialOutput("N");		//Normalize the inputs

	// Done
	initalized = true;
}

void Scene_splash::Render()
{

	// draw a box below the contine text 
	SDL_Rect boarder_rect;

	boarder_rect.h = 50;
	boarder_rect.w = GameSettings::window_width;
	boarder_rect.x = 0;
	boarder_rect.y = 240;

	float color = 255 - contineText_currentColor;

	SDL_SetRenderDrawColor(game->GetRenderer(), color, color, color, 255);
	SDL_RenderFillRect(game->GetRenderer(), &boarder_rect);

	// Game
	fryingPan_back->Render(game->GetRenderer());
	pancake->Render(game->GetRenderer());
	fryingPan_front->Render(game->GetRenderer());
	//UI
	sprite_logo->RenderSprite( game->GetRenderer(), logoPosition );
	UI_continueText->Render( game->GetRenderer() );
}

void Scene_splash::Update()
{


	fryingPan_back->Update(game->fryingPans_inputValue[panInputID]->GetGyroAxis()->y / -35.0f, 0);
	fryingPan_front->Update(game->fryingPans_inputValue[panInputID]->GetGyroAxis()->y / -35.0f, 0);

	pancake->Update(game->fryingPans_inputDelta[panInputID]->y / -20.0f,
		fryingPan_back->GetCurrentSpriteId(),
		0,	// no rotation, heat or distacne from heat is needed on the slpash screen
		0,
		0
	);

	if (!pancake->IsInPan())
		pancake_currentAirTime += Time::GetDeltaSeconds();
	else
		pancake_currentAirTime = 0.0f;
	

	if (pancake_currentAirTime > pancake_airTimeToContine)
		canContinue = true && hasEnteredPanOnce;

	if (pancake->IsInPan())
		hasEnteredPanOnce = true;

	// Contine to the maingame once we are back in the pan
	if( canContinue && pancake->IsInPan() )
		game->LoadScene("main");

	if (contineText_colorIncresse)
		contineText_currentColor += 4;
	else
		contineText_currentColor -= 4;

	if (!contineText_colorIncresse && contineText_currentColor < 0)
	{

		contineText_currentColor = 0;
		contineText_colorIncresse = true;
	}
	else if (contineText_colorIncresse && contineText_currentColor > 255)
	{

		contineText_currentColor = 255;
		contineText_colorIncresse = false;
	}

	UI_continueText->SetFontColor(contineText_currentColor, contineText_currentColor, contineText_currentColor);

}
