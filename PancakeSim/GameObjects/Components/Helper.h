#pragma once
#include "..\..\stdafx.h"
#include <chrono>

class Helper
{
public:
	static int Random()
	{
		auto now = std::chrono::system_clock::now();
		int i = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

		return rand() % i;

	}
};