#include "Work.h"
#include <future> // https://45.media.tumblr.com/0d48529ac6bb9428556a44713d9f7e55/tumblr_mzlbooK7D41rdjj9to1_500.gif

Work::Work()
{
	myFunctionPointer = nullptr;
}

Work::Work(const std::function<void()>& aWorkFunction)
{
	myFunctionPointer = aWorkFunction;
}


void Work::DoWork()
{
	if (myFunctionPointer != nullptr)
	{
		myFunctionPointer();
	}
}


Work::~Work()
{
}
