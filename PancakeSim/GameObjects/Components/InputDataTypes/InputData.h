#pragma once

#include "../Vector2.h"

class InputData
{
public:
	InputData();

	~InputData();

	void SetGyroAxis(int x, int y);
	Vector2* GetGyroAxis();

	void SetHob(int hValue);
	int GetHob();


private:

	Vector2* gyroAxis;
	int hob;

};

