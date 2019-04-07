#pragma once

class Time;
class Transform;

class Rigidbody
{
public:
	Rigidbody(Time* gameTime, Transform* attachedTransform);
	~Rigidbody();

	Time* time;
	Transform* transform;  // the transform that the RB is attached to

	void Update();


private:
	float velocity = 0.0f;

};

