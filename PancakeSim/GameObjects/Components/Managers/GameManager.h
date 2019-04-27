#pragma once
#include "stdio.h"
#include <array>
#include "..\..\..\Game.h"

//TODO: i  think i can remove this, since i we only have two scenes, no pause or menus, just splash and main game :)
enum GameState {
	Splash,		//TODO: Use this for loading ??
	Paused,
	Menu,
	MainGame
};

class GameManager
{
//Sigleton setup
public:
	
	static GameManager& GetInstance()
	{
		static GameManager instance;

		return instance;
	}

	static const int panCount = 3;

private:
	GameManager() {}
	GameManager(GameManager const&);
	GameManager& operator=(GameManager const&);

public:

	~GameManager() {};

// Main

	void AddFlip();
	int GetTotalFlips();

	void AddServedPancake(float happyness);
	int GetTotalServedPancakes();
	float GetHappyness();

	void AddScore(int score);
	int GetTotalScore();

	void ClearScore();

	typedef void (Game::* OnScoreChanged_)();
	OnScoreChanged_ onScoreChanged;

	void TriggerOnScoreChanged();

	void SetActiveGame(Game* activeGame);
	Game* GetActiveGame();

	void SetGameState( GameState state );
	GameState GetGameState();
	
	void SoundAlarm(bool shortBurst);

private:
	
	int scorePerFlip = 1;
	int scorePerPancake = 5;

	int totalPancakeFlips = 0;
	int totalPancakesServed = 0;
	float totalPancakesHappness = 0.0f;


	int totalScore = 0;

	Game* activeGame;
	GameState currentGameState = GameState::Splash;

};

