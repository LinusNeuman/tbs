#pragma once

#include "Message/BaseMessage.h"

#pragma warning  (push)
#pragma warning(disable : 4512)
struct CheckpointMessage : public BaseMessage
{
	CheckpointMessage(const RecieverTypes aRecieverType, const TilePosition & aSavedPlayerData)
	: BaseMessage(aRecieverType), myRespawnPosition(aSavedPlayerData)
	{
	}

	const TilePosition & myRespawnPosition;
};
#pragma warning (pop)