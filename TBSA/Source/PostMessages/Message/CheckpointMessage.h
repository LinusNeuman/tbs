#pragma once
#include "RecieverTypes.h"
#include "BaseMessage.h"
#include <CU/Vectors/Vector.h>

#pragma warning  (push)
#pragma warning(disable : 4512)
struct CheckpointMessage : public BaseMessage
{
	CheckpointMessage(const RecieverTypes aType, const CommonUtilities::Vector2ui &aPosition) : BaseMessage(aType), myPosition(aPosition)
	{}
	virtual ~CheckpointMessage()
	{}
	const CommonUtilities::Vector2ui &myPosition;
};
#pragma warning (pop)