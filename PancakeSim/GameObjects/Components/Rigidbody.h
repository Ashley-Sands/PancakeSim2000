#pragma once

class Time;
class Transform;
class FVector2;

class Rigidbody
{
public:
	Rigidbody(Time* gameTime, Transform* attachedTransform, FVector2* gravityForce);
	~Rigidbody();

	Time* time;
	Transform* transform;  // the transform that the RB is attached to

	void Update();

	void AddForce(float x, float y);
	FVector2* GetVelocity();

private:
	FVector2* gravity;

	FVector2* velocity;
	
};

