#include "GameManager.h"



GameManager::GameManager(){}


GameManager::~GameManager(){}

void GameManager::AddFlip()
{
	totalPancakeFlips++;
}

int GameManager::GetTotalFlips()
{
	return totalPancakeFlips;
}