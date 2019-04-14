#pragma once

class Transform;
class FVector2;

class Rigidbody
{
public:
	Rigidbody(Transform* attachedTransform, float mass);
	~Rigidbody();

	Transform* transform;  // the transform that the RB is attached to

	void Update();

	/*	Add Force to the RB current velocity (in meters per second) (takes mass into acount)
	*	@Parma x:	X Velocity to add (in meters per second)
	*	@Parma y:	Y Velocity to add (in meters per second)
	*/
	void AddForce(float x, float y);

	/*	Sets the raw velocity of the RB (in meters per second) (does not take mass into acount)
	*	@Parma x:	X Velocity to set (in meters per second)
	*	@Parma y:	Y Velocity to set (in meters per second)
	*/
	void SetVelocity(float x, float y);

	FVector2* GetVelocity();

private:
	const FVector2* gravity;

	FVector2* velocity;
	bool velocityChanged = false;

	float mass;

};

