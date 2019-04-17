#pragma once

#include "../Vector2.h"

class InputData
{
public:
	InputData();

	~InputData();

	void SetGyroAxis(int x, int y);
	Vector2* GetGyroAxis();

	void SetHobValue(int hValue);
	int GetHobValue();

	void SetHobFire(int fValue);
	int GetHobFire();


private:

	Vector2* gyroAxis;
	int onHobValue = 512;		// this is the value from the LDR, that detects if the pan in on or off the hob
	int hobFireValue = 0;

};

