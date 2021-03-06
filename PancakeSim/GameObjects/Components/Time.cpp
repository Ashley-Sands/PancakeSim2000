#include "Time.h"



Time::Time(){}
Time::~Time(){}

void Time::Init(float fps, int startTick)
{
	SetFPS(fps);
	lastUpdate_tick = startTick;
	nextUpdate_tick = lastUpdate_tick + ticksPreUpdate;
}

void Time::SetFPS(float fps)
{
	targetFPS = fps;
	ticksPreUpdate = 1000.f / fps;
}

bool Time::Update(int currentTick)
{

	if (currentTick  >= (nextUpdate_tick - (ticksPreUpdate * 0.9f)))
	{
		delta_tick = currentTick - lastUpdate_tick;
		time_since_start += delta_tick;
		lastUpdate_tick = currentTick;
		nextUpdate_tick += ticksPreUpdate;

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

float Time::GetTicksPerUpdate()
{
	return ticksPreUpdate;
}

int Time::GetTickSinceStart()
{
	return time_since_start;
}

float Time::GetSecondsSinceStart()
{
	return time_since_start / 1000.0f;
}

//Static vars
float Time::targetFPS = 60;
float Time::ticksPreUpdate = 1000.0f / Time::targetFPS;
int Time::lastUpdate_tick = 0;
float Time::nextUpdate_tick = Time::ticksPreUpdate;
int Time::delta_tick = 0;
int Time::time_since_start = 0;