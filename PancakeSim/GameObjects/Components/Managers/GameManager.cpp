#include "GameManager.h"


void GameManager::AddFlip()
{
	totalPancakeFlips++;
}

int GameManager::GetTotalFlips()
{
	return totalPancakeFlips;
}