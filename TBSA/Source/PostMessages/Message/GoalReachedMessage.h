#pragma once
#include "RecieverTypes.h"
#include "BaseMessage.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct GoalReachedMessage : public BaseMessage
{
	GoalReachedMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
	virtual ~GoalReachedMessage()
	{}
};
#pragma warning (pop)