#include "stdafx.h"
#include "PlayerController.h"
#include <GameObjects/Actor/Actor.h>
#include <Message/DijkstraMessage.h>

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

	DijkstraMessage dijkstraMessage = DijkstraMessage(RecieverTypes::eRoom, CommonUtilities::Vector2ui(mySelectedPlayer->GetPosition()), mySelectedPlayer->GetMyAP());
	SingletonPostMaster::PostMessageA(dijkstraMessage);
}

void PlayerController::NotifyPlayers() const
{
	if (mySelectedPlayer != nullptr)
	{
		mySelectedPlayer->Move(CU::Vector2ui(IsometricInput::GetMouseWindowPositionIsometric().x + .5, IsometricInput::GetMouseWindowPositionIsometric().y + .5));
	}
}
