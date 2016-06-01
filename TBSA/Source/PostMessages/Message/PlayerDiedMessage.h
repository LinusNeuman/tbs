#pragma once
#include "RecieverTypes.h"
#include "BaseMessage.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerDiedMessage: public BaseMessage
{
	PlayerDiedMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
	virtual ~PlayerDiedMessage()
	{}
};
#pragma warning (pop)