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


Player::Player()
{
	myPlayerIndex = 0;
}

Player::~Player()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayEvents,*this);
}

void Player::Init(const ActorData &aActorData, const PlayerData &aPlayerData)
{
	Actor::Init(aActorData);
	myActionPointMax = aPlayerData.myActionPointMax;
	myCurrentAP = myActionPointMax;
	myEnemyTargetIndex = USHRT_MAX;

	myIsSeen = false;
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);
	myDetectedSprite = new StaticSprite();
	myDetectedSprite->Init("Sprites/Players/Detected/PlayerDetectedSprite.dds", true);
	myDetectedSprite->SetLayer(enumRenderLayer::eGUI);
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
	SendPostMessage(PlayerAPChangedMessage(RecieverTypes::ePlayerAPChanged, myCurrentAP));
}

void Player::OnClick()
{
	SendPostMessage(PlayerIDMessage(RecieverTypes::eClickedOnPlayer, GetIndex()));
}

void Player::Draw() const
{
	if (myIsSeen == true)
	{
		if (myPlayerIndex == 0)
		{
			myDetectedSprite->Draw(GetPosition() + CU::Vector2f(-1.0f, -1.0f));
		}
		else
		{
			myDetectedSprite->Draw(GetPosition() + CU::Vector2f(-1.2f, -1.2f));
		}
	}
	Actor::Draw();
}

bool Player::RecieveMessage(const PlayerSeenMessage& aMessage)
{
	if (CommonUtilities::Point2i(myPosition) == aMessage.myPlayerPosition)
	{
		StopPath();
		myCurrentAP = 0;
		
		if (myIsSeen == false)
		{
			myIsSeen = true;
		}
		
		if (myShouldDie == true)
		{
			myIsSeen = false;
			myShouldDie = false;
			SendPostMessage(FlagPlayerDiedMessage(RecieverTypes::eFlagPlayerDied));
		}
	}
	return true;
}

void Player::AfterTurn()
{
	Actor::AfterTurn();
	myShouldDie = myIsSeen;
	myIsSeen = false;
}

void Player::PreTurn()
{
	SendPostMessage(PlayerAPChangedMessage(RecieverTypes::ePlayerAPChanged, myCurrentAP));
	myShouldDie = myIsSeen;
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
}

void Player::OnMove(CU::Vector2ui aTargetPosition)
{
	SendPostMessage(PlayerPositionChangedMessage(RecieverTypes::ePlayerPositionChanged, aTargetPosition,*this));
}

void Player::SetNoTarget()
{
	ResetObjectiveState();
	myEnemyTargetIndex = USHRT_MAX;
}

void Player::AlmostReachTarget()
{
	SendPostMessage(DijkstraMessage(RecieverTypes::eRoom, myPath[myCurrentWaypoint - 1], GetMyAP()));
}

void Player::ReachedTarget()
{
	SendPostMessage(PlayerObjectMessage(RecieverTypes::ePlayerReachedEndOfPath, *this));
}

void Player::NextToObjective()
{
	SendPostMessage(PlayerObjectMessage(RecieverTypes::ePlayerNextToObjective, *this));
}
