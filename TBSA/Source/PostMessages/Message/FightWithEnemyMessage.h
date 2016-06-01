#pragma once


#include "Message/BaseMessage.h"

#pragma warning  (push)
#pragma warning(disable : 4512)
struct FightWithEnemyMessage : public BaseMessage
{
	FightWithEnemyMessage(const RecieverTypes aRecieverType, const unsigned short & aEnemyIndex)
		: BaseMessage(aRecieverType),
		myEnemyIndex(aEnemyIndex)
	{
	}

	const unsigned short myEnemyIndex;
};
#pragma warning (pop)