#pragma once
#include "BaseMessage.h"

#pragma warning  (push)
#pragma warning(disable : 4512)
struct EnemyDirectionChangedMessage : BaseMessage
{
	EnemyDirectionChangedMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
	virtual ~EnemyDirectionChangedMessage()
	{}
};
#pragma warning (pop)