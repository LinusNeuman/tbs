#pragma once

#include <CU/Vectors/vector2.h>

struct TestPositionMessage
{
	TestPositionMessage(const CU::Vector2f & aPosition) : myPosition(aPosition)
	{}

	const CU::Vector2f myPosition;
};