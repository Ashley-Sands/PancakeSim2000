#include "Rigidbody.h"

#include "Time.h"
#include "Vector2.h"
#include "Transform.h"

Rigidbody::Rigidbody(Time* gameTime, Transform* attachedTransform, Vector2* gravityForce)
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
	// Do physics things
}
