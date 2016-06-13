#pragma once
#include "Message/BaseMessage.h"

#pragma warning  (push)
#pragma warning(disable : 4512)

struct AnimationStateMessage : public BaseMessage
{
	AnimationStateMessage(const RecieverTypes aRecieverType, const bool aIsRunning)
		: BaseMessage(aRecieverType),
		myIsRunning(aIsRunning)
	{
	}

	const bool myIsRunning;
};
#pragma warning (pop)