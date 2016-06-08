#pragma once

#include "BaseMessage.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct MouseButtonReleasedMessage :public BaseMessage
{
	MouseButtonReleasedMessage(const RecieverTypes aType, const unsigned short aKey, const bool aValue) : BaseMessage(aType),
		myKeyValue(aValue), myKey(aKey)
	{}

	const bool myKeyValue;
	const unsigned short myKey;
};
#pragma warning (pop)