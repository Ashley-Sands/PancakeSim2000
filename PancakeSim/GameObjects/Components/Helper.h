#pragma once
#include "SDL.h"
#include "Time.h"
#include "Settings/GameSettings.h"

class Helper
{
public:
	static int Random()
	{
		int mouseX, mouseY;

		SDL_GetGlobalMouseState(&mouseX, &mouseY);

		if (mouseY == 0) mouseY = 1;

		int seed = abs((mouseX * (mouseX * 0.5f)) / mouseY) * Time::GetSecondsSinceStart();

		if (seed == 0) seed = mouseY + 1;

		int r = rand() % seed;

		return r;

	}

	static void CenterRectToScreen(SDL_Rect* rectToCenter)
	{
		float screenCenter_x = GameSettings::window_width / 2.0f;
		float screenCenter_y = GameSettings::window_height / 2.0f;

		rectToCenter->x = floor( screenCenter_x - (rectToCenter->w / 2.0f) );
		rectToCenter->y = floor( screenCenter_y - (rectToCenter->h / 2.0f) );

	}

	static int Clamp(float min, float max, float n)
	{

		if ( n < min ) return min;
		else if ( n > max ) return max;
		
		
		return n;

	}
};