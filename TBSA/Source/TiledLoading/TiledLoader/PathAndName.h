#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/Vectors/vector2.h>

struct PathAndName
{
	PathAndName()
	{
		myPaths.Init(1);
	}
	CommonUtilities::GrowingArray<CommonUtilities::Point2ui> myPaths;
	std::string myName;
};
