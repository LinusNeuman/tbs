#pragma once

#include <CU/Vectors/vector2.h>

struct TestPositionMessage
{
	TestPositionMessage(const CommonUtilities::Vector2f & aPosition) : myPosition(aPosition)
	{}

	const CommonUtilities::Vector2f myPosition;
};