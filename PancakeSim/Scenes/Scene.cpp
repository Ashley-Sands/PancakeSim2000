#include "Scene.h"



Scene::Scene(Game* mainGame)
{
	game = mainGame;
}


Scene::~Scene()
{
}

bool Scene::HasInitalized()
{
	return initalized;
}