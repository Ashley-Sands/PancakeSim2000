#pragma once
#include "stdio.h"
#include <array>
#include "..\..\..\Game.h"



class GameManager
{
//Sigleton setup
public:
	
	static GameManager& GetInstance()
	{
		static GameManager instance;

		return instance;
	}

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

private:
	
	int scorePerFlip = 1;
	int scorePerPancake = 5;

	int totalPancakeFlips = 0;
	int totalPancakesServed = 0;
	float totalPancakesHappness = 0.0f;


	int totalScore = 0;

	Game* activeGame;

};

