#pragma once
#include "BaseMessage.h"

#pragma warning  (push)
#pragma warning(disable : 4512)
struct EnemyPositionChangedMessage : BaseMessage
{
	EnemyPositionChangedMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
	virtual ~EnemyPositionChangedMessage()
	{}
};
#pragma warning (pop)