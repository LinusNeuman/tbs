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
	DijkstraMessage dijkstraMessage = DijkstraMessage(RecieverTypes::eRoom, CommonUtilities::Vector2ui(mySelectedPlayer->GetPosition()) + CommonUtilities::Vector2ui(1, 1), mySelectedPlayer->GetMyAP());
	SingletonPostMaster::PostMessage(dijkstraMessage);
}

void PlayerController::SelectPlayer()
{
	++mySelectedPlayerIndex;
	if (mySelectedPlayerIndex >= myPlayers.Size())
	{
		mySelectedPlayerIndex = 0;
	}
	mySelectedPlayer = myPlayers[mySelectedPlayerIndex];

	DijkstraMessage dijkstraMessage = DijkstraMessage(RecieverTypes::eRoom, CommonUtilities::Vector2ui(mySelectedPlayer->GetPosition())+ CommonUtilities::Vector2ui(1,1), mySelectedPlayer->GetMyAP());
	SingletonPostMaster::PostMessage(dijkstraMessage);
}

void PlayerController::NotifyPlayers(CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> aPath) const
{
	if (mySelectedPlayer != nullptr)
	{
		//CU::Vector2ui position = CU::Vector2ui(IsometricInput::GetMouseWindowPositionIsometric().x + .5, IsometricInput::GetMouseWindowPositionIsometric().y + .5);
		/*std::string printOut;
		printOut += std::to_string(position.x);
		printOut += ",";
		printOut += std::to_string(position.y);
		DL_PRINT(printOut.c_str());*/

		mySelectedPlayer->SetPath(aPath);
	}
}

int PlayerController::GetPlayerAP()
{
	if (mySelectedPlayer != nullptr)
	{
		return mySelectedPlayer->GetMyAP();
	}
	else
	{
		return 0;
	}
}

void PlayerController::CostAP(const int anAP)
{
	/*if (mySelectedPlayer != nullptr)
	{
		mySelectedPlayer->
	}*/
}


