#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/Vector.h>

class Player;

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerCanPeekMessage : BaseMessage
{
	PlayerCanPeekMessage(const RecieverTypes aType, const CommonUtilities::Vector2ui &aPeekPosition, const int aPlayerID, const Player &aPlayer) : BaseMessage(aType), myPeekPosition(aPeekPosition), myPlayerID(aPlayerID), myPlayer(aPlayer)
	{}
	virtual ~PlayerCanPeekMessage()
	{}

	const CommonUtilities::Vector2ui &myPeekPosition;
	const Player &myPlayer;
	const int myPlayerID;
};
#pragma warning (pop)