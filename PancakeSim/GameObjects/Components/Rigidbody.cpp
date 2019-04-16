#include "Rigidbody.h"

#include "Settings/PhysicSettings.h"

#include "Time.h"
#include "Vector2.h"
#include "Transform.h"

Rigidbody::Rigidbody(Transform* attachedTransform, float mas)
{
	transform = attachedTransform;
	gravity = PhysicSettings::GetGravity();
	mass = mas;
	velocity = new FVector2();
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update()
{

	// Update the velocity and translate it onto the attached transform

	if (!skipGravity)	// Only apply gravity if force has not been applied (add or set)
	{
		velocity->x += ((gravity->x * mass) * Time::GetDeltaSeconds());
		velocity->y += ((gravity->y * mass) * Time::GetDeltaSeconds());
	}

	FVector2* currentPosition = transform->GetPosition();

	ClampVelocity();

	// just for now :) //TODO Update me.
	currentPosition->x += -velocity->x;
	currentPosition->y += -velocity->y;

	skipGravity = false;
}

void Rigidbody::AddForce(float x, float y)
{
	// Get the mutipler for force to take mass into acount
	// if mass is 0 prevent divByZero and silly values
	float forceMuti = 1;	
	if (mass != 0)
		forceMuti = (1.0f / mass);

	//Add Force thingy
	velocity->x += PhysicSettings::MetersTo_PxPerSecond_x( x * forceMuti );
	velocity->y += PhysicSettings::MetersTo_PxPerSecond_y( y * forceMuti );
}

void Rigidbody::SetVelocity(float x, float y)
{
	velocity->x = PhysicSettings::MetersTo_PxPerSecond_x(x);
	velocity->y = PhysicSettings::MetersTo_PxPerSecond_y(y);
	skipGravity = true;		// prevent gravity being appled gravity on the first update after velocity has be set
}

void Rigidbody::SetMaxVelocity(float maxVel)
{
	maxVelocity = maxVel * PhysicSettings::GetPxPerMeter();
}

FVector2* Rigidbody::GetVelocity()
{
	return velocity;
}

void Rigidbody::ClampVelocity()	//TODO: maybe move this into physic settings so its the same throughtout the game??
{
	// Clamp x
	if (velocity->x > maxVelocity)
		velocity->x = maxVelocity;
	else if (velocity->x < -maxVelocity)
		velocity->x = -maxVelocity;

	//Clamp y
	if (velocity->y > maxVelocity)
		velocity->y = maxVelocity;
	else if (velocity->y < -maxVelocity)
		velocity->y = -maxVelocity;

}