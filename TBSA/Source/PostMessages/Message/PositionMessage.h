#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/vector2.h>
#include <CU/NameSpaceAliases.h>

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PositionMessage : public BaseMessage
{
	PositionMessage(const RecieverTypes aReceiverType, const CU::Vector2i & aPosition) :
		BaseMessage(aReceiverType),
		myPosition(aPosition)
	{}

	const CU::Point2i myPosition;
};
#pragma warning (pop)