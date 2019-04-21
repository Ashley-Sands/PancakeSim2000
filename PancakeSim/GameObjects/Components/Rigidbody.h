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

	/* Set the max velocity in meters per sec
	*
	*/
	void SetMaxVelocity(float maxVal);

	FVector2* GetVelocity();

	void SetMass(float mass);
	float GetMass();

private:
	const FVector2* gravity;

	FVector2* velocity;
	float maxVelocity = 250.0f;		//max vel in px.
	bool skipGravity = false;

	float mass;

	// clamps velocity to max Velocity
	void ClampVelocity();

};

