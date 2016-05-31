#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/Vectors/vector2.h>

struct PathAndName
{
	PathAndName()
	{
		myPath.Init(1);
	}
	CommonUtilities::GrowingArray<CommonUtilities::Point2ui> myPath;
	std::string myName;
};
