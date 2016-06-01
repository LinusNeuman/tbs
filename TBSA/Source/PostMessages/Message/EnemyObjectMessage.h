#pragma once


#include "Message/BaseMessage.h"

class Enemy;

#pragma warning  (push)
#pragma warning(disable : 4512)
struct EnemyObjectMessage : public BaseMessage
{
	EnemyObjectMessage(const RecieverTypes aRecieverType, const Enemy & aEnemy)
		: BaseMessage(aRecieverType),
		myEnemy(aEnemy)
	{
	}

	const Enemy & myEnemy;
};
#pragma warning (pop)