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

private:
	
	static const int px_per_meter;						// since its metere per second in the real world.
	static const float gravity_metersPerSec_x;
	static const float gravity_metersPerSec_y;

	static const FVector2* px_gravity;					// gravity in px

};