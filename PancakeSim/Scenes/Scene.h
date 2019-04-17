#pragma once

class Game;

/* Base Class for scenes */
class Scene
{
public:
	Scene(Game* mainGame);
	~Scene();

	virtual void Render() = 0;
	virtual void Update() = 0;

private:

	// block default constructors
	Scene();		
	Scene(Scene const&);

	Game* game;
};

