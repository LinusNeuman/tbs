#include "stdafx.h"
#include "Enemy.h"
#include "../JsonDataStructs.h"
#include <Controllers/EnemyController.h>
#include <Message/EnemyObjectMessage.h>
#include <Message/EnemyDirectionChangedMessage.h>
#include <Message/PlayerSeenMessage.h>


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
	myCurrentPathIndex = 1;
	myAP = aEnemyData.myActionPoints;
	myViewDistance = aEnemyData.myViewDistance;
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);
	myEnemyPath.Init(1);
}

void Enemy::UpdateEnemy()
{
	if (GetActiveState() == true && GetActorState() != eActorState::eDead)
	{
		if (myPreviousDirection != myDirection)
		{
			SendPostMessage(EnemyDirectionChangedMessage(RecieverTypes::eEnemyDirectionChanged));
		}
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

void Enemy::SetDirection(eDirection aDirection)
{
	myDirection = aDirection;
}

bool Enemy::RecieveMessage(const PlayerSeenMessage& aMessage)
{
	mySomeoneSeesPlayer = true;
	if (&aMessage.myEnemy == this)
	{
		SetActorState(eActorState::eAlert);
	}
	return true;
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

int Enemy::GetViewDistance() const
{
	return myViewDistance;
}

void Enemy::OnClick()
{
	SendPostMessage(EnemyObjectMessage(RecieverTypes::eClickedOnEnemy, *this));
	//Fight();
}

void Enemy::Fight()
{
	SetActorState(eActorState::eFighting);
	SendPostMessage(EnemyObjectMessage(RecieverTypes::eEnemyAttacked, *this));
}

void Enemy::DecideAnimation()
{
	if (myState == eActorState::eIdle)
	{
		//Determine direction animation
		switch (GetDirectionEnum())
		{
		case eDirection::NORTH:
			ChangeAnimation("EnemyIdle045");
			break;
		case eDirection::NORTH_EAST:
			ChangeAnimation("EnemyIdle090");
			break;
		case eDirection::EAST:
			ChangeAnimation("EnemyIdle135");
			break;
		case eDirection::SOUTH_EAST:
			ChangeAnimation("EnemyIdle180");
			break;
		case eDirection::SOUTH:
			ChangeAnimation("EnemyIdle225");
			break;
		case eDirection::SOUTH_WEST:
			ChangeAnimation("EnemyIdle270");
			break;
		case eDirection::WEST:
			ChangeAnimation("EnemyIdle315");
			break;
		case eDirection::NORTH_WEST:
			ChangeAnimation("EnemyIdle000");
			break;
		default:
			ChangeAnimation("EnemyIdle180");
			break;
		}
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
	else if (myState == eActorState::eAlert)
	{
		//Determine direction animation
		switch (GetDirectionEnum())
		{
		case eDirection::NORTH:
			ChangeAnimation("EnemyAlert045");
			break;
		case eDirection::NORTH_EAST:
			ChangeAnimation("EnemyAlert090");
			break;
		case eDirection::EAST:
			ChangeAnimation("EnemyAlert135");
			break;
		case eDirection::SOUTH_EAST:
			ChangeAnimation("EnemyAlert180");
			break;
		case eDirection::SOUTH:
			ChangeAnimation("EnemyAlert225");
			break;
		case eDirection::SOUTH_WEST:
			ChangeAnimation("EnemyAlert270");
			break;
		case eDirection::WEST:
			ChangeAnimation("EnemyAlert315");
			break;
		case eDirection::NORTH_WEST:
			ChangeAnimation("EnemyAlert000");
			break;
		default:
			ChangeAnimation("EnemyAlert180");
			break;
		}
	}
	else if (GetActorState() == eActorState::eFighting)
	{
		ChangeAnimation("CombatAnimation");
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
