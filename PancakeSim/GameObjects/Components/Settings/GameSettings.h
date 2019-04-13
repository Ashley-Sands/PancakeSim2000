#pragma once
#include "../../../stdafx.h"

class GameSettings
{
public:
	GameSettings();
	~GameSettings();

	static const std::string GetTitle() { return "Pancake Sim 2000"; }

	static const int window_width = 800;
	static const int window_height = 600;

	static const bool fullScreen = false;

	static const int GetWindowFlags();

};

