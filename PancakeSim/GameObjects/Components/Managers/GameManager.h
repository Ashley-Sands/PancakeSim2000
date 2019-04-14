#pragma once
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

public:

	~GameManager() {};

// Main

	void AddFlip();
	int GetTotalFlips();

private:
	
	int totalPancakeFlips = 0;


};

