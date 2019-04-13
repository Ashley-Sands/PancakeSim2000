#pragma once
class Time
{
public:
	Time();
	~Time();

	static void Init(float fps, int startTick);
	static void SetFPS(float fps);
	
	static bool Update(int currentTick);		// returns true once enought ticks have pass to meet the target FPS.

	static int GetDelta();						//in ticks
	static float GetDeltaSeconds();

private:
	static float targetFPS;// = 60;

	static float ticksPreUpdate;// = 1000.0f / targetFPS;

	static int lastUpdate_tick;// = 0;
	static float nextUpdate_tick;// = ticksPreUpdate;
	static int delta_tick;// = 0;

};

