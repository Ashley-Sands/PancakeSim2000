#include "Time.h"



Time::Time()
{
}

Time::Time(int fps, int startTick)
{
	SetFPS(fps);
	lastUpdate_tick = startTick;
}

Time::~Time()
{
}

void Time::SetFPS(int fps)
{
	targetFPS = fps;
	ticksPreUpdate = 1000 / fps;
}

bool Time::Update(int currentTick)
{

	if (currentTick - lastUpdate_tick >= (ticksPreUpdate - 1) )
	{
		delta_tick = currentTick - lastUpdate_tick;
		lastUpdate_tick = currentTick;
		return true;
	}

	return false;

}

int Time::GetDelta()
{
	return delta_tick;
}

float Time::GetDeltaSeconds()
{
	return delta_tick / 1000.0f;
}