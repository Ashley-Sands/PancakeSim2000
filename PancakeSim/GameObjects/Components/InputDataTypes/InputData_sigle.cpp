#include "InputData_single.h"

InputData_single::InputData_single()
{}

InputData_single::~InputData_single()
{}

void InputData_single::SetWhisking(bool b)
{
	whisking = b;
}

bool InputData_single::IsWhisking()
{
	return whisking;
}