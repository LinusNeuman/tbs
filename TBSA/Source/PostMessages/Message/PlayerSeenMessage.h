#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/vector2.h>
#include <CU/NameSpaceAliases.h>

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerSeenMessage : public BaseMessage
{
	PlayerSeenMessage(const RecieverTypes aReceiverType, const CU::Vector2i & aPlayerPosition, const Enemy & aEnemy) :
		BaseMessage(aReceiverType),
		myPlayerPosition(aPlayerPosition),
		myEnemy(aEnemy)
	{}

	const CU::Point2i myPlayerPosition;
	const Enemy & myEnemy;
};
#pragma warning (pop)