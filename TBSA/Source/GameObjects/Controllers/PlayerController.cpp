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
	SingletonPostMaster::PostMessage(dijkstraMessage);
}

void PlayerController::NotifyPlayers() const
{
	if (mySelectedPlayer != nullptr)
	{
		CU::Vector2ui position = CU::Vector2ui(IsometricInput::GetMouseWindowPositionIsometric().x + .5, IsometricInput::GetMouseWindowPositionIsometric().y + .5);
		std::string printOut;
		printOut += static_cast<float>(position.x);
		printOut += ",";
		printOut += static_cast<float>(position.y);
		DL_PRINT(printOut.c_str());

		mySelectedPlayer->Move(position);
	}
}
