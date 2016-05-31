#pragma once
#include "BaseMessage.h"

#pragma warning  (push)
#pragma warning(disable : 4512)
struct EnemyChangedDirectionMessage : BaseMessage
{
	EnemyChangedDirectionMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
	virtual ~EnemyChangedDirectionMessage()
	{}
};
#pragma warning (pop)