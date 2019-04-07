#include "Rigidbody.h"

#include "Time.h"
#include "Transform.h"

Rigidbody::Rigidbody(Time* gameTime, Transform* attachedTransform)
{
	time = gameTime;
	transform = attachedTransform;
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update()
{
	// Do physics things
}
