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
	myIsDeadeastFlag = false;
	myCurrentPathIndex = 0;
	myAP = aEnemyData.myActionPoints;
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);
	myEnemyPath.Init(1);
}

void Enemy::UpdateEnemy()
{
	if (GetActiveState() == true && GetActorState() != eActorState::eDead)
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
		else if (myEnemyPath.Size() == 0)
		{
			myController->EnemyDone();
		}

		if (mySomeoneSeesPlayer == true)
		{
			myController->EnemyDone();
			StopPath();
		}
	}
	else
	{
		myController->EnemyDone();
	}
}

void Enemy::ReachedTarget()
{
	SendPostMessage(EnemyObjectMessage(RecieverTypes::eEnemyReachedEndOfPath, *this));
}

void Enemy::AlmostReachTarget()
{
	myController->EnemyDone();
}

void Enemy::RecieveMessage(const PlayerSeenMessage& aMessage)
{
	mySomeoneSeesPlayer = true;
}

void Enemy::SetEnemyPath(PathArray aEnemyPath)
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
	if (myState == eActorState::eIdle)
	{
		//Determine direction animation
		/*switch (GetDirectionEnum())
		{
		case eDirection::NORTH:
			ChangeAnimation("playerIdle045");
			break;
		case eDirection::NORTH_EAST:
			ChangeAnimation("playerIdle090");
			break;
		case eDirection::EAST:
			ChangeAnimation("playerIdle135");
			break;
		case eDirection::SOUTH_EAST:
			ChangeAnimation("playerIdle180");
			break;
		case eDirection::SOUTH:
			ChangeAnimation("playerIdle225");
			break;
		case eDirection::SOUTH_WEST:
			ChangeAnimation("playerIdle270");
			break;
		case eDirection::WEST:
			ChangeAnimation("playerIdle315");
			break;
		case eDirection::NORTH_WEST:
			ChangeAnimation("playerIdle000");
			break;
		default:
			ChangeAnimation("playerIdle180");
			break;
		}*/
	}
	else if (myState == eActorState::eWalking)
	{
		//Determine direction animation
		switch (GetDirectionEnum())
		{
		case eDirection::NORTH:
			ChangeAnimation("EnemyWalk045");
			break;
		case eDirection::NORTH_EAST:
			ChangeAnimation("EnemyWalk090");
			break;
		case eDirection::EAST:
			ChangeAnimation("EnemyWalk135");
			break;
		case eDirection::SOUTH_EAST:
			ChangeAnimation("EnemyWalk180");
			break;
		case eDirection::SOUTH:
			ChangeAnimation("EnemyWalk225");
			break;
		case eDirection::SOUTH_WEST:
			ChangeAnimation("EnemyWalk270");
			break;
		case eDirection::WEST:
			ChangeAnimation("EnemyWalk315");
			break;
		case eDirection::NORTH_WEST:
			ChangeAnimation("EnemyWalk000");
			break;
		default:
			ChangeAnimation("EnemyWalk180");
			break;
		}
	}
	else if (GetActorState() == eActorState::eFighting)
	{
		ChangeAnimation("CombatAnimation");
	}
	else if (GetActorState() == eActorState::eIdle)
	{
		ChangeAnimation("EnemyTurn");
	}
	else if (GetActorState() == eActorState::eDead)
	{
		if (myAnimations.GetAnimationIsRunning() == false)
		{
			if (myIsDeadeastFlag == false)
			{
				ChangeAnimation("DeathAnimation");
				myIsDeadeastFlag = true;
			}
			else
			{
				ChangeAnimation("DeadestState");
			}
		}
	}
}
