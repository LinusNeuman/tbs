#pragma once
#include "RecieverTypes.h"
#include "BaseMessage.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct FlagGoalReachedMessage : public BaseMessage
{
	FlagGoalReachedMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
	virtual ~FlagGoalReachedMessage()
	{}
};
#pragma warning (pop)