#include "stdafx.h"
#include "Player.h"
#include "Rend/Renderer.h"
#include <Rend/StaticSprite.h>
#include "../JsonDataStructs.h"


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
}

void Player::DecideAnimation()
{
	if (myState == eActorState::eIdle)
	{
		ChangeAnimation("PlayerIdle");
	}
	else if (myState == eActorState::eWalking)
	{
		ChangeAnimation("PlayerTurn");
	}
}