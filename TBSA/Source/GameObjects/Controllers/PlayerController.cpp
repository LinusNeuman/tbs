#include "stdafx.h"
#include "PlayerController.h"
#include <GameObjects/Actor/Actor.h>
#include <Message/DijkstraMessage.h>
#include <NavGraph/Vertex/NavVertex.h>
#include <Message/NavigationClearMessage.h>
#include "../../GameStates/GameStates/PlayState.h"

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
	DijkstraMessage dijkstraMessage = DijkstraMessage(RecieverTypes::eRoom, CommonUtilities::Vector2ui(mySelectedPlayer->GetPosition()) , mySelectedPlayer->GetMyAP());
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

	DijkstraMessage dijkstraMessage = DijkstraMessage(RecieverTypes::eRoom, CommonUtilities::Vector2ui(mySelectedPlayer->GetPosition()), mySelectedPlayer->GetMyAP());
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
	if (mySelectedPlayer != nullptr)
	{
		//mySelectedPlayer;
	}
}

void PlayerController::Update(const CommonUtilities::Time& aTime)
{
	const CommonUtilities::Vector2ui mousePosition = CommonUtilities::Vector2ui(IsometricInput::GetMouseWindowPositionIsometric() + CommonUtilities::Vector2f(0.5, 0.5));


	if (IsometricInput::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft))
	{
		if (myPlayState->GetTile(mousePosition).CheckIfWalkable() == true && myPlayState->GetTile(mousePosition).GetVertexHandle()->IsSearched() == true)
		{
			CommonUtilities::GrowingArray<int> indexPath = myPlayState->GetTile(mousePosition).GetVertexHandle()->GetPath();
			CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> positionPath;
			positionPath.Init(indexPath.Size());

			for (size_t i = 0; i < indexPath.Size(); i++)
			{
				positionPath.Add(CommonUtilities::Vector2ui(myPlayState->GetTile(indexPath[indexPath.Size() - (i + 1)]).GetPosition()));
			}
			if (GetPlayerAP() >= positionPath.Size())
			{
				NotifyPlayers(positionPath);
				SingletonPostMaster::PostMessageA(NavigationClearMessage(RecieverTypes::eRoom));
			}
		}

	}

	if (IsometricInput::GetKeyPressed(DIK_TAB) == true)
	{
		SelectPlayer();
	}
}

void PlayerController::SetMyPlayState(PlayState& aPlayStateRef)
{
	myPlayState = &aPlayStateRef;
}
