#include "stdafx.h"
#include "PlayerController.h"
#include "Actor/Actor.h"


PlayerController::PlayerController()
{
	myPlayers.Init(2);
}


PlayerController::~PlayerController()
{
}

void PlayerController::AddPlayer(Actor* aPlayer)
{
	myPlayers.Add(aPlayer);
	mySelectedPlayer = myPlayers[0];
}

void PlayerController::SelectPlayer()
{
	if (mySelectedPlayer == myPlayers[0])
	{
		mySelectedPlayer = myPlayers[1];
	}
	else
	{
		mySelectedPlayer = myPlayers[0];
	}
}

void PlayerController::NotifyPlayers() const
{
	if (mySelectedPlayer != nullptr)
	{
		mySelectedPlayer->Move(GetInput::GetMouseWindowPosition() / 64.f);
	}
}
