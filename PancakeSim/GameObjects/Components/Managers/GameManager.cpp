#include "GameManager.h"


void GameManager::AddFlip()
{
	totalPancakeFlips++;

	TriggerOnScoreChanged();

}

int GameManager::GetTotalFlips()
{
	return totalPancakeFlips;
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