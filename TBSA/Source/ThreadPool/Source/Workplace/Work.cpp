#include "Work.h"
#include <future> // https://mz-prod.s3.amazonaws.com/uploads/photo/file/208173/small_23c05ce08bd50b09b8cf9f09b758aefa-5470.jpg

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
