#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/Vector.h>

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerPositionChangedMessage : BaseMessage
{
	PlayerPositionChangedMessage(const RecieverTypes aType, const CommonUtilities::Vector2ui &aPosition) : BaseMessage(aType), myPosition(aPosition)
	{}
	virtual ~PlayerPositionChangedMessage()
	{}

	const CommonUtilities::Vector2ui &myPosition;
};
#pragma warning (pop)