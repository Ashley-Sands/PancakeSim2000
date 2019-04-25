#include "GameManager.h"


void GameManager::AddFlip()
{
	totalPancakeFlips++;

	AddScore(scorePerFlip);

}

int GameManager::GetTotalFlips()
{
	return totalPancakeFlips;
}

void GameManager::AddServedPancake(float happyness)
{
	totalPancakesServed++;
	totalPancakesHappness += happyness;

	if (happyness > 0)
		AddScore(scorePerPancake);
	else
		TriggerOnScoreChanged();
}

int GameManager::GetTotalServedPancakes()
{
	return totalPancakesServed;
}

float GameManager::GetHappyness()
{
	return (totalPancakesHappness + 1) / (totalPancakesServed + 1); // +1 to avoid divByZero and so it starts at 1.0
}

void GameManager::AddScore(int score)
{
	totalScore += score;

	TriggerOnScoreChanged();

}

int GameManager::GetTotalScore()
{
	return totalScore;
}

void GameManager::ClearScore()
{
	totalPancakeFlips = 0;
	totalScore = 0;
}

void GameManager::TriggerOnScoreChanged()
{
	(activeGame->*onScoreChanged)();
}

void GameManager::SetActiveGame(Game* actGame)
{
	activeGame = actGame;
}

Game* GameManager::GetActiveGame()
{
	return activeGame;
}

void GameManager::SetGameState( GameState state)
{
	currentGameState = state;
}

GameState GameManager::GetGameState()
{
	return currentGameState;
}

void GameManager::SoundAlarm(bool shortBurst)
{
	activeGame->HandleSerialOutput( shortBurst ? "e" : "f" );
}