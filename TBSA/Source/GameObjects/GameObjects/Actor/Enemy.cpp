#include "stdafx.h"
#include "Enemy.h"
#include "../JsonDataStructs.h"
#include <Controllers/EnemyController.h>


Enemy::Enemy()
{
	
}


Enemy::~Enemy()
{
}

void Enemy::Init(const ActorData &aActorData, const EnemyData &aEnemyData)
{
	Actor::Init(aActorData);
	//Do stuff with enemydata
	myHasMoved = false;
	myHasTurned = false;
	myCurrentPathIndex = 0;
}

void Enemy::UpdateEnemy()
{
	if (GetActiveState() == true)
	{
		if (myHasMoved == false && myEnemyPath.Size() > 0)
		{
			CommonUtilities::GrowingArray<CommonUtilities::Point2ui> path;
			path.Init(1);

			for (size_t i = 0; i < static_cast<size_t>(myAP); i++)
			{
				if (myHasTurned == false)
				{
					path.Add(myEnemyPath[myCurrentPathIndex]);
					++myCurrentPathIndex;
					if (myCurrentPathIndex >= myEnemyPath.Size())
					{
						myHasTurned = true;
						--myCurrentPathIndex;
					}
				}
				else
				{
					--myCurrentPathIndex;
					path.Add(myEnemyPath[myCurrentPathIndex]);
					if (myCurrentPathIndex <= 0)
					{
						myHasTurned = false;
						++myCurrentPathIndex;
					}
				}
			}

			SetPath(path);
			myHasMoved = true;
		}
	}
	else
	{
		myController->EnemyDone();
	}
}

void Enemy::ReachedTarget()
{
	myController->EnemyDone();
}

void Enemy::SetEnemyPath(CommonUtilities::GrowingArray<CommonUtilities::Point2ui> aEnemyPath)
{
	myEnemyPath = aEnemyPath;
}

void Enemy::Reset()
{
	myHasMoved = false;
}
