#include "GameSettings.h"
#include "SDL.h"


GameSettings::GameSettings()
{
}


GameSettings::~GameSettings()
{
}

const int GameSettings::GetWindowFlags()
{
	int flags = 0;

	if (fullScreen)
		flags = flags | SDL_WINDOW_FULLSCREEN;

	return flags;
}