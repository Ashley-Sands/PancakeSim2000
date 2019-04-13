#pragma once

class Transform;
class FVector2;

class Rigidbody
{
public:
	Rigidbody(Transform* attachedTransform, FVector2* gravityForce);
	~Rigidbody();

	Transform* transform;  // the transform that the RB is attached to

	void Update();

	void AddForce(float x, float y);
	FVector2* GetVelocity();
	void SetVelocity(float x, float y);

private:
	FVector2* gravity;

	FVector2* velocity;
	
};

