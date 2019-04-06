#pragma once
class Time
{
public:
	Time();
	Time(int fps, int startTick);
	~Time();

	void SetFPS(int fps);
	
	bool Update(int currentTick);		// returns true once enought ticks have pass to meet the target FPS.

	int GetDelta();						//in ticks
	float GetDeltaSeconds();

private:
	int targetFPS = 60;

	float ticksPreUpdate = 1000.0f / targetFPS;

	int lastUpdate_tick = 0;
	float nextUpdate_tick = ticksPreUpdate;
	int delta_tick = 0;

};

