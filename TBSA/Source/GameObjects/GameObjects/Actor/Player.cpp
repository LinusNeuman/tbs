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
#include <Message/PlayerDiedMessage.h>


Player::Player()
{
}

Player::~Player()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayEvents,*this);
}

void Player::Init(const ActorData &aActorData, const PlayerData &aPlayerData)
{
	Actor::Init(aActorData);
	//Do stuff with playerdata
	myActionPointMax = aPlayerData.myActionPointMax;
	myCurrentAP = myActionPointMax;

	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);
}

void Player::FreshTurn()
{
	myCurrentAP = myActionPointMax;
}

int Player::GetMyAP() const
{
	return myCurrentAP;
}

void Player::CostAP(const int aCost)
{
	assert(aCost <= myCurrentAP && "AP cost exceeded player's available AP");
	myCurrentAP -= aCost;
}

void Player::ReachedTarget()
{
	SendPostMessage(DijkstraMessage(RecieverTypes::eRoom, myPath[myCurrentWaypoint - 1], GetMyAP()));
}

void Player::OnClick()
{
	SendPostMessage(PlayerObjectMessage(RecieverTypes::eChangeSelectedPlayer, *this));
}

void Player::RecieveMessage(const PlayerSeenMessage& aMessage)
{
	if (CommonUtilities::Point2i(myPosition) == aMessage.myPlayerPosition)
	{
		if (myIsSeen == false)
		{
			myIsSeen = true;
		}
		else
		{
			SendPostMessage(PlayerDiedMessage(RecieverTypes::ePlayEvents));
		}
	}
}

void Player::DecideAnimation()
{
	if (myState == eActorState::eIdle)
	{
		ChangeAnimation("PlayerIdle");
	}
	else if (myState == eActorState::eWalking)
	{
		//Determine direction animation
		switch (GetDirectionEnum())
		{
		case eDirection::NORTH: 
			ChangeAnimation("gingerWalk045");
			break;
		case eDirection::NORTH_EAST: 
			ChangeAnimation("gingerWalk090");
			break;
		case eDirection::EAST: 
			ChangeAnimation("gingerWalk135");
			break;
		case eDirection::SOUTH_EAST: 
			ChangeAnimation("gingerWalk180");
			break;
		case eDirection::SOUTH: 
			ChangeAnimation("gingerWalk225");
			break;
		case eDirection::SOUTH_WEST:
			ChangeAnimation("gingerWalk270");
			break;
		case eDirection::WEST: 
			ChangeAnimation("gingerWalk315");
			break;
		case eDirection::NORTH_WEST: 
			ChangeAnimation("gingerWalk00");
			break;
		default: break;
		}
	}
}

void Player::OnMove(CU::Vector2ui aTargetPosition)
{
}
