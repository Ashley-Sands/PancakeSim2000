#include "scene_splash.h"
#include "..\GameObjects\Components\Components.h"
#include "..\Game.h"

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
	sprite_logo->SetSprite(game->GetRenderer(), "Sprites/SimPancake_2000.png");

	logoPosition->x = 0;
	logoPosition->y = 0;
	logoPosition->w = sprite_logo->GetSpriteSize()->x;
	logoPosition->h = sprite_logo->GetSpriteSize()->y;

}

void Scene_splash::Render()
{
	sprite_logo->RenderSprite(game->GetRenderer(), logoPosition);
}

void Scene_splash::Update()
{

	currentPosition += Time::GetDeltaSeconds();


}
