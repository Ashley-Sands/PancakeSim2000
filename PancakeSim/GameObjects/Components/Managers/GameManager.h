#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();

	static void AddFlip();
	static int GetTotalFlips();

private:
	
	static int totalPancakeFlips;


};

