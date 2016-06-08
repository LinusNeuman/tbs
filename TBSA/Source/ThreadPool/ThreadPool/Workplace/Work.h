#pragma once
#include <functional>
class Work
{
public:
	Work();
	Work(const std::function<void(void)>& aWorkFunction);
	~Work();

	void DoWork();
private:
	std::function<void(void)> myFunctionPointer;
};

