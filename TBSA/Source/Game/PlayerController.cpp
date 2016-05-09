#include "stdafx.h"
#include "PlayerController.h"
#include "Actor/Actor.h"


PlayerController::PlayerController()
{
	myPlayers.Init(2);
	mySelectedPlayer = nullptr;
}


PlayerController::~PlayerController()
{
}

void PlayerController::AddPlayer(Actor* aPlayer)
{
	myPlayers.Add(aPlayer);
}

void PlayerController::SelectPlayer(Actor *aPlayer)
{
	if (myPlayers.Find(aPlayer) != myPlayers.FoundNone)
	{
		mySelectedPlayer = aPlayer;
	}
}

void PlayerController::NotifyPlayers(const CU::Time aDeltaTime) const
{
	if (mySelectedPlayer != nullptr)
	{
		mySelectedPlayer->Move(GetInput::GetMouseWindowPosition() / 64.f, aDeltaTime);
	}
}
