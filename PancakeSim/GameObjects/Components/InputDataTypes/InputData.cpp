#include "InputData.h"

InputData::InputData()
{
	gyroAxis = new Vector2();
};

InputData::~InputData()
{
	delete gyroAxis;
};

void InputData::SetGyroAxis(int x, int y)
{
	gyroAxis->x = x;
	gyroAxis->y = y;
}

Vector2* InputData::GetGyroAxis() 
{ 
	return gyroAxis;
}

void InputData::SetHobValue(int hValue)
{
	// Clamp 0, 1023
	if (hValue < 0.0f) hValue = 0;
	else if (hValue > 1023) hValue = 1023;

	onHobValue = hValue;

}

int InputData::GetHobValue()
{
	return onHobValue;
}

void InputData::SetHobFire(int fValue)
{
	hobFireValue = fValue;
}

int InputData::GetHobFire()
{
	return hobFireValue;
}