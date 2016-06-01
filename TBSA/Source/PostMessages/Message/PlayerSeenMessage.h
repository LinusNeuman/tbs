#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/vector2.h>
#include <CU/NameSpaceAliases.h>

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerSeenMessage : public BaseMessage
{
	PlayerSeenMessage(const RecieverTypes aReceiverType, const CU::Vector2i & aPlayerPosition) :
		BaseMessage(aReceiverType),
		myPlayerPosition(aPlayerPosition)
	{}

	const CU::Point2i myPlayerPosition;
};
#pragma warning (pop)