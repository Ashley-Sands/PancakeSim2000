#pragma once


class InputData_single
{
public:
	InputData_single();

	~InputData_single();

	void SetWhisking(bool b);
	bool IsWhisking();

	void SetPourRotation(int rot);
	int GetPourRotation();

private:
	bool whisking = false;
	int pourRotation = 0;

};