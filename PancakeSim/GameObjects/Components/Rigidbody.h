#pragma once

class Time;
class Transform;
class Vector2;

class Rigidbody
{
public:
	Rigidbody(Time* gameTime, Transform* attachedTransform, Vector2* gravityForce);
	~Rigidbody();

	Time* time;
	Transform* transform;  // the transform that the RB is attached to

	void Update();

	void AddForce(Vector2* force);
	Vector2* GetVelocity();

private:
	Vector2* gravity;

	Vector2* velocity;
	
};

