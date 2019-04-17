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

void InputData::SetHob(int hValue)
{

	hob = hValue;

}

int InputData::GetHob()
{
	return hob;
}