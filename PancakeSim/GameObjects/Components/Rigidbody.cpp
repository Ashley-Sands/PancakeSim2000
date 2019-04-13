#include "Rigidbody.h"

#include "Time.h"
#include "Vector2.h"
#include "Transform.h"

Rigidbody::Rigidbody(Transform* attachedTransform, FVector2* gravityForce)
{
	transform = attachedTransform;
	gravity = gravityForce;
	velocity = new FVector2();
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update()
{

	//TODO Update to physic settings :)

	// Update th velocity and translate it onto the attached transform
	velocity->x += ( gravity->x * Time::GetDeltaSeconds() );
	velocity->y += ( gravity->y * Time::GetDeltaSeconds() );

	FVector2* currentPosition = transform->GetPosition();

	// just for now :) //TODO Update me.
	currentPosition->x += -velocity->x;
	currentPosition->y += -velocity->y;

}

void Rigidbody::AddForce(float x, float y)
{
	//Add Force thingy
	velocity->x += x;
	velocity->y += y;

}

FVector2* Rigidbody::GetVelocity()
{
	return velocity;
}

void Rigidbody::SetVelocity(float x, float y)
{
	velocity->x = x;
	velocity->y = y;
}