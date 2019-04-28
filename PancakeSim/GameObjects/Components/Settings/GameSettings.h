#pragma once
#include "../../../stdafx.h"

class GameSettings
{
public:
	GameSettings();
	~GameSettings();

	static const std::string GetTitle() { return "Sim Pancake 2000"; }

	static const int window_width = 1280;
	static const int window_height = 800;

	static const bool fullScreen = false;

	static const int GetWindowFlags();

};

