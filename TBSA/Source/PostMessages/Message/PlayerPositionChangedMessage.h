#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/Vector.h>

class Player;

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerPositionChangedMessage : BaseMessage
{
	PlayerPositionChangedMessage(const RecieverTypes aType, const CommonUtilities::Vector2ui &aPosition, const Player &aPlayer) : BaseMessage(aType), myPosition(aPosition), myPlayer(aPlayer)
	{}
	virtual ~PlayerPositionChangedMessage()
	{}

	const CommonUtilities::Vector2ui &myPosition;
	const Player &myPlayer;
};
#pragma warning (pop)