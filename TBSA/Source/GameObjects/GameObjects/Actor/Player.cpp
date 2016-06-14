#include "stdafx.h"
#include "Player.h"
#include "Rend/Renderer.h"
#include <Rend/StaticSprite.h>
#include "../JsonDataStructs.h"
#include <Message/DijkstraMessage.h>
#include <Message/ColliderMessage.h>
#include <Collision/BoxCollider.h>
#include <Message/PlayerObjectMesssage.h>
#include <Message/PlayerSeenMessage.h>
#include <Message/FlagPlayerDiedMessage.h>
#include <Message/PlayerPositionChangedMessage.h>
#include <Message/PlayerAPChangedMessage.h>
#include <Message/PlayerIDMessage.h>
#include <Message/DijkstraMessage.h>


Player::Player()
{
	myPlayerIndex = 0;
	myIsSelected = false;
}

Player::~Player()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayEvents, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eAnimationState, *this);
}

void Player::Init(const ActorData &aActorData, const PlayerData &aPlayerData)
{
	Actor::Init(aActorData);
	myActionPointMax = aPlayerData.myActionPointMax;
	myAttackCost = aPlayerData.myAttackCost;
	myPeekCost = aPlayerData.myPeekCost;
	myCurrentAP = myActionPointMax;
	myEnemyTargetIndex = USHRT_MAX;
	myIsSeen = false;
	myIsInFight = false;
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eAnimationState, *this);


	myAPBox.SetPos(myPosition);
	myAPBox.Reset();
}

void Player::FreshTurn()
{
	if (myIsSeen == true)
	{
		myCurrentAP = 0;
	}
	else
	{
		myCurrentAP = myActionPointMax;
	}
}

int Player::GetMyAP() const
{
	return myCurrentAP;
}

int Player::GetPreviousAP() const
{
	return myPreviousAP;
}

void Player::CostAP(const int aCost)
{
	assert(aCost <= myCurrentAP && "AP cost exceeded player's available AP");
	myCurrentAP -= aCost;
	SendPostMessage(PlayerAPChangedMessage(RecieverTypes::ePlayerAPChanged, myCurrentAP));
	SendPostMessage(DijkstraMessage(RecieverTypes::eRoom, CommonUtilities::Vector2ui(myPosition), GetMyAP()));

}

void Player::SuggestCostAP(const int aSuggestCost)
{
	myAPBox.SetCost(aSuggestCost);
}



void Player::OnClick()
{
	SendPostMessage(PlayerIDMessage(RecieverTypes::eClickedOnPlayer, GetIndex()));
	SendPostMessage(PlayerAPChangedMessage(RecieverTypes::ePlayerAPChanged, myCurrentAP));
}

void Player::Draw() const
{
	Actor::Draw();
	myAPBox.Draw();
}

bool Player::RecieveMessage(const PlayerSeenMessage& aMessage)
{
	if (CommonUtilities::Point2i(myPosition) == aMessage.myPlayerPosition)
	{
		StopPath();
		myPreviousAP = myCurrentAP;
		myCurrentAP = 0;
		
		if (myIsSeen == false)
		{
			myIsSeen = true;
			SetActorState(eActorState::eAlert);
		}
	}
	return true;
}


void Player::AfterTurn()
{
	Actor::AfterTurn();
	if (myIsSeen == true)
	{
		SendPostMessage(FlagPlayerDiedMessage(RecieverTypes::eFlagPlayerDied));
	}
}

int Player::GetPeekCost() const
{
	return myPeekCost;
}


int Player::GetAttackCost() const
{
	return myAttackCost - 1; // remove 1 for the movement cost of going to the same tile as the enemy.
}

void Player::Update(const CU::Time& aDeltaTime)
{
	Actor::Update(aDeltaTime);

	myAPBox.Update();
	myAPBox.SetAP(myCurrentAP);
	myAPBox.SetPos(myPosition);
	if (myIsSelected == true)
	{
		myAPBox.Animate(aDeltaTime);
	}
	else
	{
		myAPBox.Reset();
	}

	
}

void Player::ResetObjectiveState()
{
	Actor::ResetObjectiveState();
	myEnemyTargetIndex = USHRT_MAX;
}

void Player::PreTurn()
{
	SendPostMessage(PlayerAPChangedMessage(RecieverTypes::ePlayerAPChanged, myCurrentAP));
	myIsSeen = false;
}

void Player::DecideAnimation()
{
	if (myState == eActorState::eIdle)
	{
		//Determine direction animation
		switch (GetDirectionEnum())
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
		}
	}
	else if (myState == eActorState::eWalking)
	{
		//Determine direction animation
		switch (GetDirectionEnum())
		{
		case eDirection::NORTH: 
			ChangeAnimation("playerWalk045");
			break;
		case eDirection::NORTH_EAST: 
			ChangeAnimation("playerWalk090");
			break;
		case eDirection::EAST: 
			ChangeAnimation("playerWalk135");
			break;
		case eDirection::SOUTH_EAST: 
			ChangeAnimation("playerWalk180");
			break;
		case eDirection::SOUTH: 
			ChangeAnimation("playerWalk225");
			break;
		case eDirection::SOUTH_WEST:
			ChangeAnimation("playerWalk270");
			break;
		case eDirection::WEST: 
			ChangeAnimation("playerWalk315");
			break;
		case eDirection::NORTH_WEST: 
			ChangeAnimation("playerWalk000");
			break;
		default:
			ChangeAnimation("playerWalk180");
			break;
		}
	}
	else if (myState == eActorState::eAlert)
	{
		//Determine direction animation
		switch (GetDirectionEnum())
		{
		case eDirection::NORTH:
			ChangeAnimation("playerAlert045");
			break;
		case eDirection::NORTH_EAST:
			ChangeAnimation("playerAlert090");
			break;
		case eDirection::EAST:
			ChangeAnimation("playerAlert135");
			break;
		case eDirection::SOUTH_EAST:
			ChangeAnimation("playerAlert180");
			break;
		case eDirection::SOUTH:
			ChangeAnimation("playerAlert225");
			break;
		case eDirection::SOUTH_WEST:
			ChangeAnimation("playerAlert270");
			break;
		case eDirection::WEST:
			ChangeAnimation("playerAlert315");
			break;
		case eDirection::NORTH_WEST:
			ChangeAnimation("playerAlert000");
			break;
		default:
			ChangeAnimation("playerAlert180");
			break;
		}
	}
	else if (myState == eActorState::eFighting)
	{
		ChangeAnimation("");
	}
}

void Player::OnMove(CU::Vector2ui aTargetPosition)
{
	//SendPostMessage(PlayerPositionChangedMessage(RecieverTypes::ePlayerPositionChanged, aTargetPosition,*this));
}

void Player::SetNoTarget()
{
	ResetObjectiveState();
}

void Player::AlmostReachTarget()
{
	SendPostMessage(DijkstraMessage(RecieverTypes::eRoom, myPath[myCurrentWaypoint - 1], GetMyAP()));
	SetPreviousPosition(myPosition);
}

void Player::ReachedTarget()
{
	SendPostMessage(PlayerObjectMessage(RecieverTypes::ePlayerReachedEndOfPath, *this));
}

void Player::ReachedWaypoint()
{
	SendPostMessage(PlayerPositionChangedMessage(RecieverTypes:: ePlayerPositionChanged, CU::Vector2ui::Zero, *this));
}

void Player::NextToObjective()
{
	SendPostMessage(PlayerObjectMessage(RecieverTypes::ePlayerNextToObjective, *this));
}
