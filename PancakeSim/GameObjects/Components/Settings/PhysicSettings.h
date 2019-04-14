#pragma once

class FVector2;

class PhysicSettings
{
public:
	PhysicSettings();
	~PhysicSettings();

	/*Inits static vars*/
	static void Init();

	/* Returns Gravity in px */
	static const FVector2* GetGravity();

	static void MetersTo_PxPerSecond(FVector2* metersPerSecond);

	static float MetersTo_PxPerSecond_x(float x_metersPerSecond);
	static float MetersTo_PxPerSecond_y(float y_metersPerSecond);

	//static void MetersTo_PxPerSecond(float* x, float* y);

private:
	
	static const int px_per_meter;						// since its metere per second in the real world.
	static const float gravity_metersPerSec_x;
	static const float gravity_metersPerSec_y;

	static const FVector2* px_gravity;					// gravity in px

};