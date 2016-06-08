#pragma once
#include <Windows.h>

class ThreadHelper
{
public:
	ThreadHelper();
	~ThreadHelper();

	static void SetThreadName(DWORD dwThreadID, char* threadName);
};