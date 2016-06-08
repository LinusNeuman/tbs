#pragma once

#include "Message/BaseMessage.h"

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerIDMessage : public BaseMessage
{
	PlayerIDMessage(const RecieverTypes aRecieverType, const unsigned short aPlayerID)
		: BaseMessage(aRecieverType),
		myPlayerID(aPlayerID)
	{
	}

	const unsigned short myPlayerID;
};
#pragma warning (pop)