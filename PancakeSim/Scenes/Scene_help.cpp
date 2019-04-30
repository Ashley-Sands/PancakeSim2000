#include "Scene_help.h"
#include "SDL.h"
#include "..\GameObjects\Components\Settings\GameSettings.h"
#include "..\GameObjects\Components\UI\TextTransform.h"
#include "..\GameObjects\Components\Components.h"
#include "..\Game.h"
#include <string>

Scene_help::Scene_help(Game* game) : Scene(game)
{
	sprite_logo = new Sprite();
	logoPosition = new SDL_Rect();

	sprite_help = new Sprite();
	helpPosition = new SDL_Rect();
}


Scene_help::~Scene_help()
{
}

void Scene_help::Init() 
{

	// Logo
	sprite_logo->SetSprite(game->GetRenderer(), "Sprites/SimPancake_2000.png");

	logoPosition->w = sprite_logo->GetSpriteSize()->x / 2;
	logoPosition->h = sprite_logo->GetSpriteSize()->y / 2;

	Helper::CenterRectToScreen( /*out*/ logoPosition);
	logoPosition->y = 50;

	sprite_help->SetSprite(game->GetRenderer(), "Sprites/help.png");

	helpPosition->w = sprite_help->GetSpriteSize()->x ;
	helpPosition->h = sprite_help->GetSpriteSize()->y ;

	Helper::CenterRectToScreen( /*out*/ helpPosition);
	helpPosition->y = 250;

}


void Scene_help::Render()
{

	// draw a box below the help text
	SDL_Rect boarder_rect;

	boarder_rect.h = GameSettings::window_height * 0.8f;
	boarder_rect.w = GameSettings::window_width * 0.8f;
	boarder_rect.x = GameSettings::window_width * 0.1f;
	boarder_rect.y = GameSettings::window_height * 0.1f;

	float color = 255;

	SDL_SetRenderDrawColor( game->GetRenderer(), color, color, color, 255 );
	SDL_RenderFillRect( game->GetRenderer(), &boarder_rect );

	sprite_logo->RenderSprite( game->GetRenderer(), logoPosition );
	sprite_help->RenderSprite(game->GetRenderer(), helpPosition);


}

void Scene_help::Update()
{

}
