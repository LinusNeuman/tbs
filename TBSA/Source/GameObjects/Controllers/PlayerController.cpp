#include "stdafx.h"
#include "PlayerController.h"
#include <GameObjects/Actor/Actor.h>
#include <Message/DijkstraMessage.h>
#include <NavGraph/Vertex/NavVertex.h>
#include <Message/NavigationClearMessage.h>
#include <GameObjects/Actor/Player.h>


#include <PostMaster/SingletonPostMaster.h>
#include <Message/SetMainCameraMessage.h>

#include <Collision/PointCollider.h>
#include <Message/ColliderMessage.h>
#include <Message/PlayerObjectMesssage.h>
#include <Message/ActorPositionChangedMessage.h>
#include <Message/PlayerAddedMessage.h>
#include <Message/PlayerSeenMessage.h>
#include <Rend/RenderConverter.h>
#include <Message/PlayerReachedTargetMessage.h>
#include <Message/EnemyObjectMessage.h>
#include <GameObjects/Actor/Enemy.h>
#include <Message/FightWithEnemyMessage.h>

#define EDGE_SCROLL_LIMIT -50.05f

const float CameraSpeed = 10.f;
const float PlayerFoWRadius = 5.f;

PlayerController::PlayerController()
{
	myPlayers.Init(2);
	mySelectedPlayerIndex = 0;
	mySelectedPlayer = nullptr;
	myClickedOnPlayer = false;
	myClickedOnEnemy = false;
}

PlayerController::~PlayerController()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eChangeSelectedPlayer, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayerAdded, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eEnemyChangedDirection, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eActorPositionChanged, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eClickedOnEnemy, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayerChangedTarget, *this);
}

void PlayerController::Init()
{
	SendPostMessage(SetMainCameraMessage(RecieverTypes::eCamera, myCamera));
	SingletonPostMaster::AddReciever(RecieverTypes::eChangeSelectedPlayer, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eActorPositionChanged, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayerAdded, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eEnemyChangedDirection, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayerChangedTarget, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eClickedOnEnemy, *this);
}

void PlayerController::AddPlayer(Player* aPlayer)
{
	myPlayers.Add(aPlayer);
	mySelectedPlayer = myPlayers[mySelectedPlayerIndex];
	SendPostMessage(PlayerAddedMessage(RecieverTypes::ePlayerAdded));
	DijkstraMessage dijkstraMessage = DijkstraMessage(RecieverTypes::eRoom, CommonUtilities::Vector2ui(mySelectedPlayer->GetPosition()) , mySelectedPlayer->GetMyAP());
	SendPostMessage(dijkstraMessage);
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
	SendPostMessage(dijkstraMessage);
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
		return 0;
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
		myClickedOnPlayer = false;
		myClickedOnEnemy = false;

		PointCollider tempCollider;

		tempCollider.ChangePosition(IsometricInput::GetMouseWindowPositionIsometric());

		SendPostMessage(ColliderMessage(RecieverTypes::eMouseClicked, tempCollider));

		
		if (myClickedOnPlayer == false)
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

				if (myClickedOnEnemy == true)
				{
					positionPath.RemoveAtIndex(positionPath.Size() - 1);
				}

				if (GetPlayerAP() >= (positionPath.Size() - 1))
				{
					CostAP(positionPath.Size() - 1);
					NotifyPlayers(positionPath);
					SendPostMessage(NavigationClearMessage(RecieverTypes::eRoom));
				}
			}
		}

	}

	if (IsometricInput::GetKeyPressed(DIK_TAB) == true)
	{
		SelectPlayer();
	}
}

void PlayerController::ConstantUpdate(const CommonUtilities::Time& aDeltaTime)
{
}

void PlayerController::SetFloor(GameFloor & aFloor)
{
	myFloor = &aFloor;
}

void PlayerController::PrePlayer()
{
	DijkstraMessage dijkstraMessage = DijkstraMessage(RecieverTypes::eRoom, CommonUtilities::Vector2ui(mySelectedPlayer->GetPosition()), mySelectedPlayer->GetMyAP());
	SendPostMessage(dijkstraMessage);
}

void PlayerController::RefillAllAP()
{
	for (unsigned int i = 0; i < myPlayers.Size(); ++i)
	{
		myPlayers[i]->FreshTurn();
	}
}

void PlayerController::SetCameraPositionToPlayer(int aIndex)
{
	myCamera.SetPos(myPlayers[aIndex]->GetPosition());
}

void PlayerController::AfterPlayerTurn()
{
	for (size_t i = 0; i < myPlayers.Size(); i++)
	{
		myPlayers[i]->AfterTurn();
	}
}

void PlayerController::RecieveMessage(const PlayerObjectMessage & aMessage)
{
	if (mySelectedPlayer != &aMessage.myPlayer)
	{
		myClickedOnPlayer = true;
		SelectPlayer();
	}
}

void PlayerController::RecieveMessage(const ActorPositionChangedMessage& aMessage)
{
	if (myFloor->GetTile(aMessage.myPosition.x, aMessage.myPosition.y).GetInEnemyFov() == true)
	{
		DL_PRINT("An enemy can see you!");
		PlayerSeen(CommonUtilities::Point2i(aMessage.myPosition));
	}
}

void PlayerController::RecieveMessage(const PlayerChangedTargetMessage& aMessage)
{
	ResetTileShaders();
	myDebugStart.clear();
	myDebugEnd.clear();
	for (unsigned short iPlayer = 0; iPlayer < myPlayers.Size(); iPlayer++)
	{
		CreatePlayerFoV(CU::Vector2f(myPlayers[iPlayer]->GetTargetPosition()), PlayerFoWRadius);
	}
}

void PlayerController::RecieveMessage(const PlayerAddedMessage& aMessage)
{
	ResetTileShaders();
	for (unsigned short iPlayer = 0; iPlayer < myPlayers.Size(); iPlayer++)
	{
		CreatePlayerFoV(myPlayers[iPlayer]->GetPosition(), PlayerFoWRadius);
	}
}

void PlayerController::RecieveMessage(const EnemyObjectMessage & aMessage)
{
	myClickedOnEnemy = true;
	mySelectedPlayer->SetTargetEnemy(aMessage.myEnemy.GetIndex());
	SendPostMessage(FightWithEnemyMessage(RecieverTypes::eStartFight, mySelectedPlayer->GetEnemyTarget()));
}

void PlayerController::PlayerSeen(CommonUtilities::Point2i aPlayerPosition)
{
	SendPostMessage(PlayerSeenMessage(RecieverTypes::ePlayEvents, aPlayerPosition));
}

void PlayerController::RecieveMessage(const EnemyChangedDirectionMessage& aMessage)
{
	for (unsigned short iPlayer = 0; iPlayer < myPlayers.Size(); iPlayer++)
	{
		if (myFloor->GetTile(CU::Vector2ui(myPlayers[iPlayer]->GetPosition().x, myPlayers[iPlayer]->GetPosition().y)).GetInEnemyFov() == true)
		{
			DL_PRINT("An enemy can see you!");
			PlayerSeen(CommonUtilities::Point2i(myPlayers[iPlayer]->GetPosition()));
		}
	}
}

void PlayerController::RayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition)
{
	bool hasAlreadyBeenBlocked = false;
	CU::Vector2f position = aPosition;
	CU::Vector2f secondPosition = anotherPosition;
	double x0, x1, y0, y1;
	x0 = position.x;
	y0 = position.y;
	x1 = secondPosition.x;
	y1 = secondPosition.y;

	myDebugStart.push_back(position);
	myDebugEnd.push_back(secondPosition);


	int dx = abs(static_cast<int>(x1 - x0));
	int dy = abs(static_cast<int>(y1 - y0));
	int x = static_cast<int>(x0);
	int y = static_cast<int>(y0);
	int n = 1 + dx + dy;
	int x_inc = (x1 > x0) ? 1 : -1;
	int y_inc = (y1 > y0) ? 1 : -1;
	int error = dx - dy;
	dx *= 2;
	dy *= 2;

	for (; n > 0; --n)
	{
		if (hasAlreadyBeenBlocked == true && myFloor->GetTile(x, y).GetTileType() == eTileType::BLOCKED)
		{
			myFloor->GetTile(x, y).SetVisible(true);
			break;
		}
		if (hasAlreadyBeenBlocked == true && myFloor->GetTile(x, y).GetTileType() != eTileType::BLOCKED)
		{
			break;
		}
		if (myFloor->GetTile(x, y).GetTileType() == eTileType::BLOCKED)
		{
			myFloor->GetTile(x, y).SetVisible(true);
			hasAlreadyBeenBlocked = true;
		}
		myFloor->GetTile(x, y).SetVisible(true);
		
		if (error > 0)
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}

}

void PlayerController::CreatePlayerFoV(const CU::Vector2f& aPosition, float aRadius)
{
	
	int r, xc, yc, pk, x, y;
	xc = static_cast<int>(aPosition.x);
	yc = static_cast<int>(aPosition.y);
	r = static_cast<int>(aRadius);
	pk = 3 - 2 * r;
	x = 0; y = r;
	CalculateCircleRayTrace(CU::Vector2f(static_cast<float>(x), static_cast<float>(y)), CU::Vector2f(static_cast<float>(xc), static_cast<float>(yc)));
	while (x < y)
	{
		if (pk <= 0)
		{
			pk = pk + (4 * x) + 6;
			CalculateCircleRayTrace(CU::Vector2f(static_cast<float>(++x), static_cast<float>(y)), CU::Vector2f(static_cast<float>(xc), static_cast<float>(yc)));
		}
		else
		{
			pk = pk + (4 * (x - y)) + 10;
			CalculateCircleRayTrace(CU::Vector2f(static_cast<float>(++x), static_cast<float>(--y)), CU::Vector2f(static_cast<float>(xc), static_cast<float>(yc)));
		}
	}

}
	
void PlayerController::CalculateCircleRayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& aPlayerPosition)
{
	
	RayTrace(aPlayerPosition, CU::Vector2f(aPosition.x + aPlayerPosition.x, aPosition.y + aPlayerPosition.y));
	RayTrace(aPlayerPosition, CU::Vector2f(-aPosition.x + aPlayerPosition.x, aPosition.y + aPlayerPosition.y));
	RayTrace(aPlayerPosition, CU::Vector2f(aPosition.x + aPlayerPosition.x, -aPosition.y + aPlayerPosition.y));
	RayTrace(aPlayerPosition, CU::Vector2f(-aPosition.x + aPlayerPosition.x, -aPosition.y + aPlayerPosition.y));
	RayTrace(aPlayerPosition, CU::Vector2f(aPosition.y + aPlayerPosition.x, aPosition.x + aPlayerPosition.y));
	RayTrace(aPlayerPosition, CU::Vector2f(aPosition.y + aPlayerPosition.x, -aPosition.x + aPlayerPosition.y));
	RayTrace(aPlayerPosition, CU::Vector2f(-aPosition.y + aPlayerPosition.x, aPosition.x + aPlayerPosition.y));
	RayTrace(aPlayerPosition, CU::Vector2f(-aPosition.y + aPlayerPosition.x, -aPosition.x + aPlayerPosition.y));

}

int PlayerController::CalculatePoint(float aValue) const
{
	if (aValue <= 0)
	{
		return static_cast<int>(floor(aValue));
	}
	return static_cast<int>(ceil(aValue));
}

void PlayerController::ResetTileShaders()
{
	for (unsigned int i = 0; i < myFloor->Size(); i++)
	{
		myFloor->GetTile(i).SetVisible(false);
	}
}
