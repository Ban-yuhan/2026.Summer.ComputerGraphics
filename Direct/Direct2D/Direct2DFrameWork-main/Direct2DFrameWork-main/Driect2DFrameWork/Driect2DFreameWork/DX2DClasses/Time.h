#pragma once
#include <Windows.h>

class CTime
{
public:
	static float GetDeltaTime()
	{
		return timeGetTime() / 1000.0f;
	}
};