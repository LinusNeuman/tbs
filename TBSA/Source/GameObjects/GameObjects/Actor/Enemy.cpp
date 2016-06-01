#include "stdafx.h"
#include "Enemy.h"
#include "../JsonDataStructs.h"
#include <Controllers/EnemyController.h>
#include <Message/EnemyObjectMessage.h>


Enemy::Enemy()
{
	myIndex = 0;
}


Enemy::~Enemy()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayEvents, *this);
}

void Enemy::Init(const ActorData &aActorData, const EnemyData &aEnemyData)
{
	Actor::Init(aActorData);
	//Do stuff with enemydata
	myHasMoved = false;
	myHasTurned = false;
	mySomeoneSeesPlayer = false;
	myCurrentPathIndex = 0;

	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);
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

		if (mySomeoneSeesPlayer == true && myAtTarget == true)
		{
			myController->EnemyDone();
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

void Enemy::RecieveMessage(const PlayerSeenMessage& aMessage)
{
	mySomeoneSeesPlayer = true;
}

void Enemy::SetEnemyPath(CommonUtilities::GrowingArray<CommonUtilities::Point2ui> aEnemyPath)
{
	myEnemyPath = aEnemyPath;
}

void Enemy::Reset()
{
	myHasMoved = false;
	mySomeoneSeesPlayer = false;
}





void Enemy::OnClick()
{
	SendPostMessage(EnemyObjectMessage(RecieverTypes::eClickedOnEnemy, *this));
	//Fight();
}

void Enemy::Fight()
{
	SetActorState(eActorState::eFighting);
}

void Enemy::DecideAnimation()
{
	if (GetActorState() == eActorState::eFighting)
	{
		ChangeAnimation("CombatAnimation");
	}
}