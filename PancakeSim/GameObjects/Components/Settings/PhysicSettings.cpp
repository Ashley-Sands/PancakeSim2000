#include "PhysicSettings.h"
#include "../Vector2.h"

//Static vars
const int   PhysicSettings::px_per_meter = 60;
const float PhysicSettings::gravity_metersPerSec_x = 0.0f;
const float PhysicSettings::gravity_metersPerSec_y = -9.82f;
const FVector2* PhysicSettings::px_gravity;

PhysicSettings::PhysicSettings(){}

PhysicSettings::~PhysicSettings(){}

// Static Methods

void PhysicSettings::Init()
{
	if (px_gravity != nullptr) return;	//TODO: add print to console	

	px_gravity = new FVector2(gravity_metersPerSec_x * (float)px_per_meter, gravity_metersPerSec_y * (float)px_per_meter);

}

const FVector2* PhysicSettings::GetGravity()
{
	return px_gravity;
}

void PhysicSettings::MetersTo_PxPerSecond(FVector2 * metersPerSecond)
{
	metersPerSecond->x *= (float)px_per_meter;
	metersPerSecond->y *= (float)px_per_meter;
}

void PhysicSettings::MetersTo_PxPerSecond(float& x, float& y)
{
	x *= (float)px_per_meter;
	y *= (float)px_per_meter;
}

