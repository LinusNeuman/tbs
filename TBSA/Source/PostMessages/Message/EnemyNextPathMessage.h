#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/Vector.h>

class Enemy;

#pragma warning  (push)
#pragma warning(disable : 4512)
struct EnemyNextPathMessage : BaseMessage
{
	EnemyNextPathMessage(const RecieverTypes aType, const CommonUtilities::Vector2ui &aPosition, const Enemy & aEnemy) : BaseMessage(aType), myPosition(aPosition), myEnemy(aEnemy)
	{}
	virtual ~EnemyNextPathMessage()
	{}

	const CommonUtilities::Vector2ui &myPosition;
	const Enemy & myEnemy;
};
#pragma warning (pop)