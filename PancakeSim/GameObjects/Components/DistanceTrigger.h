#pragma once

class Transform;
class FVector2;


// Simple Distance Trigger
class DistanceTrigger
{

public:

	DistanceTrigger(Transform* transform);
	~DistanceTrigger();

	// returns true when triggered
	bool Trigger(Transform* otherTransform);

	//set the trigger distance in px.
	void SetTriggerDistance(float distance);

	Transform* GetTransform();

private:

	Transform* attachedTransform;

	float triggerDistance = 150;		//px




};

