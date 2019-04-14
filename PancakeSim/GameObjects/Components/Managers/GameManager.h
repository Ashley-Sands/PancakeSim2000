#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();

	static void AddFlip();

private:
	
	static int totalPancakesFlips = 0;


};

