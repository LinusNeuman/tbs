#include "stdafx.h"
#include "Player.h"
#include "Rend/Renderer.h"
#include <Rend/StaticSprite.h>
#include "../JsonDataStructs.h"
#include <Message/DijkstraMessage.h>


Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(const ActorData &aActorData, const PlayerData &aPlayerData)
{
	Actor::Init(aActorData);
	//Do stuff with playerdata
	myActionPointMax = aPlayerData.myActionPointMax;
	myCurrentAP = myActionPointMax;
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

void Player::DecideAnimation()
{
	if (myState == eActorState::eIdle)
	{
		ChangeAnimation("PlayerIdle");
	}
	else if (myState == eActorState::eWalking)
	{
		//Determine direction animation
		if (myVelocity.x < 0.f && myVelocity.y < 0.f)
		{
			ChangeAnimation("gingerWalk00");
		}
		else if (myVelocity.x == 0.f && myVelocity.y < 0.f)
		{
			ChangeAnimation("gingerWalk045");
		}
		else if (myVelocity.x > 0.f && myVelocity.y < 0.f)
		{
			ChangeAnimation("gingerWalk090");
		}
		else if (myVelocity.x > 0.f && myVelocity.y == 0.f)
		{
			ChangeAnimation("gingerWalk135");
		}
		else if (myVelocity.x > 0.f && myVelocity.y > 0.f)
		{
			ChangeAnimation("gingerWalk180");
		}
		else if (myVelocity.x == 0.f && myVelocity.y > 0.f)
		{
			ChangeAnimation("gingerWalk225");
		}
		else if (myVelocity.x < 0.f && myVelocity.y > 0.f)
		{
			ChangeAnimation("gingerWalk270");
		}
		else if (myVelocity.x < 0.f && myVelocity.y == 0.f)
		{
			ChangeAnimation("gingerWalk315");
		}
	}
}
