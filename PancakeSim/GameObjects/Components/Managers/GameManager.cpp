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