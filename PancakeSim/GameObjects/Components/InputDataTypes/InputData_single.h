#pragma once


class InputData_single
{
public:
	InputData_single();

	~InputData_single();

	void SetWhisking(bool b);
	bool IsWhisking();

private:
	bool whisking = false;

};