#pragma once

#include "Message/BaseMessage.h"

class Player;

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerObjectMessage : public BaseMessage
{
	PlayerObjectMessage(const RecieverTypes aRecieverType, const Player & aPlayer)
		: BaseMessage(aRecieverType),
		myPlayer(aPlayer)
	{
	}

	const Player & myPlayer;
};
#pragma warning (pop)