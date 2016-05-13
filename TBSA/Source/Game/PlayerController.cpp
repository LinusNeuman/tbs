#include "stdafx.h"
#include "PlayerController.h"
#include "Actor/Actor.h"


PlayerController::PlayerController()
{
	myPlayers.Init(2);
	mySelectedPlayerIndex = 0;
	mySelectedPlayer = nullptr;
}


PlayerController::~PlayerController()
{
}

void PlayerController::AddPlayer(Actor* aPlayer)
{
	myPlayers.Add(aPlayer);
	mySelectedPlayer = myPlayers[mySelectedPlayerIndex];
}

void PlayerController::SelectPlayer()
{
	++mySelectedPlayerIndex;
	if (mySelectedPlayerIndex >= myPlayers.Size())
	{
		mySelectedPlayerIndex = 0;
	}
	mySelectedPlayer = myPlayers[mySelectedPlayerIndex];
}

void PlayerController::NotifyPlayers() const
{
	if (mySelectedPlayer != nullptr)
	{
		mySelectedPlayer->Move(CU::Vector2f(IsometricInput::GetMouseWindowPositionIsometric().x, IsometricInput::GetMouseWindowPositionIsometric().y));
	}
}
