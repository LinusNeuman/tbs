#pragma once

#include "Message/BaseMessage.h"

class Player;

#pragma warning  (push)
#pragma warning(disable : 4512)
struct CurrentPlayerAP : public BaseMessage
{
	CurrentPlayerAP(const RecieverTypes aRecieverType, const int aCurrentPlayerAP, const int aCurrentPlayerID)
		: BaseMessage(aRecieverType),
		myCurrentPlayerAP(aCurrentPlayerAP),
		myCurrentPlayerID(aCurrentPlayerID)
	{
	}

	const int myCurrentPlayerAP;
	const int myCurrentPlayerID;
};
#pragma warning (pop)