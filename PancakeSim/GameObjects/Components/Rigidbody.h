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



private:
	float velocity = 0.0f;

	Vector2* gravity;

};

