#include "GameManager.h"


void GameManager::AddFlip()
{
	totalPancakeFlips++;
}

int GameManager::GetTotalFlips()
{
	return totalPancakeFlips;
void GameManager::SetActiveGame(Game* actGame)
{
	activeGame = actGame;
}

Game* GameManager::GetActiveGame()
{
	return activeGame;
}