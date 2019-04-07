#include "Rigidbody.h"

#include "Time.h"
#include "Vector2.h"
#include "Transform.h"

Rigidbody::Rigidbody(Time* gameTime, Transform* attachedTransform, FVector2* gravityForce)
{
	time = gameTime;
	transform = attachedTransform;
	gravity = gravityForce;
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update()
{
	// Update th velocity and translate it onto the attached transform
	velocity->x += ( gravity->x * time->GetDeltaSeconds() );
	velocity->y += ( gravity->y * time->GetDeltaSeconds() );

	Vector2* currentPosition = transform->GetPosition();

	// just for now :) //TODO Update me.
	currentPosition->x += velocity->x;
	currentPosition->y += velocity->y;

}

void Rigidbody::AddForce(FVector2* force)
{
	//Add Force thingy
	velocity->x += force->x;
	velocity->y += force->y;

}

FVector2* Rigidbody::GetVelocity()
{
	return velocity;
}