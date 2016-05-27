#include "stdafx.h"
#include "PlayerController.h"
#include <GameObjects/Actor/Actor.h>
#include <Message/DijkstraMessage.h>
#include <NavGraph/Vertex/NavVertex.h>
#include <Message/NavigationClearMessage.h>
#include <GameObjects/Actor/Player.h>


#include <PostMaster/SingletonPostMaster.h>
#include <Message/SetMainCameraMessage.h>

#define EDGE_SCROLL_LIMIT -50.05f

const float CameraSpeed = 10.f;

PlayerController::PlayerController()
{
	myPlayers.Init(2);
	mySelectedPlayerIndex = 0;
	mySelectedPlayer = nullptr;
}


PlayerController::~PlayerController()
{
}

void PlayerController::Init()
{
	SendPostMessage(SetMainCameraMessage(RecieverTypes::eCamera, myCamera));
}

void PlayerController::AddPlayer(Player* aPlayer)
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
		mySelectedPlayer->CostAP(anAP);
	}
}

void PlayerController::Update(const CommonUtilities::Time& aTime)
{
	const CommonUtilities::Vector2ui mousePosition = CommonUtilities::Vector2ui(IsometricInput::GetMouseWindowPositionIsometric() + CommonUtilities::Vector2f(0.5, 0.5));

#pragma region CameraControls

	if (IsometricInput::GetKeyDown(DIK_W) || IsometricInput::GetMouseWindowPositionNormalizedSpace().y <= EDGE_SCROLL_LIMIT)
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(0.f, -CameraSpeed) * aTime.GetSeconds()));
	}
	if (IsometricInput::GetKeyDown(DIK_S) || IsometricInput::GetMouseWindowPositionNormalizedSpace().y >= 1.f - EDGE_SCROLL_LIMIT)
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(0.f, CameraSpeed) * aTime.GetSeconds()));
	}
	if (IsometricInput::GetKeyDown(DIK_A) || IsometricInput::GetMouseWindowPositionNormalizedSpace().x <= EDGE_SCROLL_LIMIT)
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(-CameraSpeed, 0.0f) * aTime.GetSeconds()));
	}
	if (IsometricInput::GetKeyDown(DIK_D) || IsometricInput::GetMouseWindowPositionNormalizedSpace().x >= 1.f - EDGE_SCROLL_LIMIT)
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(CameraSpeed, 0.0f) * aTime.GetSeconds()));
	}

#pragma endregion

	if (IsometricInput::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft))
	{
		if (myFloor->GetTile(mousePosition).CheckIfWalkable() == true && myFloor->GetTile(mousePosition).GetVertexHandle()->IsSearched() == true)
		{
			CommonUtilities::GrowingArray<int> indexPath = myFloor->GetTile(mousePosition).GetVertexHandle()->GetPath();
			CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> positionPath;
			positionPath.Init(indexPath.Size());

			for (size_t i = 0; i < indexPath.Size(); i++)
			{
				positionPath.Add(CommonUtilities::Vector2ui(myFloor->GetTile(indexPath[indexPath.Size() - (i + 1)]).GetPosition()));
			}
			if (GetPlayerAP() >= (positionPath.Size() -1))
			{
				CostAP(positionPath.Size() -1);
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

void PlayerController::SetFloor(GameFloor & aFloor)
{
	myFloor = &aFloor;
}

void PlayerController::PrePlayer()
{
	DijkstraMessage dijkstraMessage = DijkstraMessage(RecieverTypes::eRoom, CommonUtilities::Vector2ui(mySelectedPlayer->GetPosition()), mySelectedPlayer->GetMyAP());
	SingletonPostMaster::PostMessage(dijkstraMessage);
}

void PlayerController::RefillAllAP()
{
	for (unsigned int i = 0; i < myPlayers.Size(); ++i)
	{
		myPlayers[i]->FreshTurn();
	}
}

