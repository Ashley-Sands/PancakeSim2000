#include "scene_splash.h"
#include "..\GameObjects\Components\Components.h"
#include "..\Game.h"
#include "..\GameObjects\Components\Managers\GameManager.h"
#include "..\GameObjects\Components\Helper.h"
#include "..\GameObjects\Components\UI\TextTransform.h"

Scene_splash::Scene_splash(Game* game) : Scene(game)
{
	sprite_logo = new Sprite();
	logoPosition = new SDL_Rect();
}


Scene_splash::~Scene_splash()
{

	delete sprite_logo;
	delete logoPosition;
	
}

void Scene_splash::Init()
{
	
	UI_continueText = new TextTransform(game->GetMainFontFace());
	UI_continueText->SetText("Flip A Pancake To Continue");
	UI_continueText->SetScale(0.5f, 0.5f);
	UI_continueText->SetPosition(250, 250);

	sprite_logo->SetSprite(game->GetRenderer(), "Sprites/SimPancake_2000.png");

	logoPosition->w = sprite_logo->GetSpriteSize()->x / 2;
	logoPosition->h = sprite_logo->GetSpriteSize()->y / 2;

	Helper::CenterRectToScreen( /*out*/ logoPosition );
	logoPosition->y = 50;

	game->SetBackgroundColor(50, 50, 50);
}

void Scene_splash::Render()
{
	sprite_logo->RenderSprite( game->GetRenderer(), logoPosition );
	UI_continueText->Render( game->GetRenderer() );
}

void Scene_splash::Update()
{

	currentPosition += Time::GetDeltaSeconds();

	if( currentPosition > length)
		GameManager::GetInstance().SetGameState(GameState::MainGame);

	float newColor =  Helper::Random();
	UI_continueText->SetFontColor(newColor, newColor, newColor);

}
