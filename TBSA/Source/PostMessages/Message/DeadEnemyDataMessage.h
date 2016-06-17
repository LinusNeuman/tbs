#pragma once

#include "Message/BaseMessage.h"

struct SavedDeadEnemy;

#pragma warning  (push)
#pragma warning(disable : 4512)
struct DeadEnemyMessage : public BaseMessage
{
	DeadEnemyMessage(const RecieverTypes aRecieverType, const SavedDeadEnemy & aSavedDeadEnemy)
		: BaseMessage(aRecieverType), myEnemyData(aSavedDeadEnemy)
	{
	}

	const SavedDeadEnemy & myEnemyData;
};
#pragma warning (pop)