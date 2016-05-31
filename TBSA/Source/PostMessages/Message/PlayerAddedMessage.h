#pragma once
#include "BaseMessage.h"

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerAddedMessage : BaseMessage
{
	PlayerAddedMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
	virtual ~PlayerAddedMessage()
	{}
};
#pragma warning (pop)