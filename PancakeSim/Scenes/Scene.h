#pragma once

class Game;

/* Base Class for scenes */
class Scene
{
public:
	Scene(Game* mainGame);
	~Scene();

	void Render() = 0;
	void Update() = 0;

private:

	// block default constructors
	Scene();		
	Scene(Scene const&);

	Game* game;
};

