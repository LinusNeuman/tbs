#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/vector2.h>

struct TestPositionMessage : public BaseMessage
{
	TestPositionMessage(const RecieverTypes aType, const CommonUtilities::Vector2f & aPosition) : myPosition(aPosition), BaseMessage(aType)
	{}

	const CommonUtilities::Vector2f myPosition;
};