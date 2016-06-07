#pragma once
#include "RecieverTypes.h"
#include "BaseMessage.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerAPChangedMessage : BaseMessage
{
	PlayerAPChangedMessage(const RecieverTypes aType, const unsigned int aNewAPValue) : BaseMessage(aType), myAP(aNewAPValue)
	{}
	virtual ~PlayerAPChangedMessage()
	{}


	unsigned int myAP;
};
#pragma warning (pop)