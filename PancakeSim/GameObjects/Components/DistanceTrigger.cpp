#include "DistanceTrigger.h"
#include "Transform.h"
#include "Vector2.h"
#include <math.h>

DistanceTrigger::DistanceTrigger(Transform* transform)
{
	attachedTransform = transform;
}

DistanceTrigger::~DistanceTrigger() 
{}

bool DistanceTrigger::Trigger(Transform* otherTransform) 
{
	// caculate the current distance
	float currentDistance =  pow(attachedTransform->GetPosition()->x - otherTransform->GetPosition()->x, 2);
		  currentDistance += pow(attachedTransform->GetPosition()->y - otherTransform->GetPosition()->y, 2);
		
		  currentDistance = sqrt(currentDistance);

	// trigger if in range
	if (currentDistance <= triggerDistance)
		return true;
	else
		return false;

}

Transform* DistanceTrigger::GetTransform()
{
	return attachedTransform;
}


