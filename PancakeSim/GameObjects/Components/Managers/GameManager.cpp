#include "GameManager.h"



GameManager::GameManager(){}


GameManager::~GameManager(){}

int GameManager::totalPancakeFlips = 0;

void GameManager::AddFlip()
{
	totalPancakeFlips++;
}

int GameManager::GetTotalFlips()
{
	return totalPancakeFlips;
}