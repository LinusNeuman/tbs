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
#include <Message/PlayerPositionChangedMessage.h>
#include <Message/PlayerAddedMessage.h>
#include <Message/PlayerSeenMessage.h>
#include <Rend/RenderConverter.h>
#include <Message/EnemyObjectMessage.h>
#include <GameObjects/Actor/Enemy.h>
#include <Message/FightWithEnemyMessage.h>
#include <Message/GoalReachedMessage.h>
#include <Message/FlagGoalReachedMessage.h>
#include <Message/PlayerCanPeekMessage.h>
#include <Message/PlayerIDMessage.h>
#include <Message/PlayerAPChangedMessage.h>
#include <Message/TextMessage.h>
#include <Message/PositionMessage.h>
#include <GUI/Messaging/Generic/GUIMessage.h>

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

	mySelectPlayerSound = new SoundEffect();
	mySelectPlayerSound->Init("Sounds/GUI/HoverMenuItem.ogg");

	myAlertSound = new SoundEffect();
	myAlertSound->Init("Sounds/SFX/alert.wav");
}

PlayerController::~PlayerController()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eChangeSelectedPlayer, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayerAdded, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eEnemyPositionChanged, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eEnemyDirectionChanged, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eEnemyAttacked, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eEnemyDead, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayerPositionChanged, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eClickedOnEnemy, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayerChangedTarget, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayerReachedEndOfPath, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayerNextToObjective, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eClickedOnPlayer, *this);
	SingletonPostMaster::RemoveReciever(*this);
}

void PlayerController::Init()
{
	SendPostMessage(SetMainCameraMessage(RecieverTypes::eCamera, myCamera));
	SingletonPostMaster::AddReciever(RecieverTypes::eChangeSelectedPlayer, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayerPositionChanged, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayerAdded, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eEnemyPositionChanged, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eEnemyDirectionChanged, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eEnemyAttacked, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eEnemyDead, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayerChangedTarget, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eClickedOnEnemy, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayerReachedEndOfPath, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayerNextToObjective, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eClickedOnPlayer, *this);
}

void PlayerController::AddPlayer(Player* aPlayer)
{
	myPlayers.Add(aPlayer);
	myPlayers.GetLast()->SetIndex(myPlayers.Size() - 1);
	mySelectedPlayer = myPlayers[mySelectedPlayerIndex];
	myPlayers[mySelectedPlayerIndex]->SetSelected(true);
	SendPostMessage(PlayerAddedMessage(RecieverTypes::ePlayerAdded));
	DijkstraMessage dijkstraMessage = DijkstraMessage(RecieverTypes::eRoom, CommonUtilities::Vector2ui(mySelectedPlayer->GetPosition()) , mySelectedPlayer->GetMyAP());
	SendPostMessage(dijkstraMessage);
}

void PlayerController::SelectPlayer()
{
	myPlayers[mySelectedPlayerIndex]->SetSelected(false);
	++mySelectedPlayerIndex;
	if (mySelectedPlayerIndex >= myPlayers.Size())
	{
		mySelectedPlayerIndex = 0;
	}
	mySelectedPlayer = myPlayers[mySelectedPlayerIndex];
	myPlayers[mySelectedPlayerIndex]->SetSelected(true);

	SetCameraPositionToPlayer(mySelectedPlayerIndex);
	
	mySelectPlayerSound->Play(0.2f);

	DijkstraMessage dijkstraMessage = DijkstraMessage(RecieverTypes::eRoom, TilePosition(mySelectedPlayer->GetPosition()), mySelectedPlayer->GetMyAP());
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
	const TilePosition mousePosition = TilePosition(IsometricInput::GetMouseWindowPositionIsometric() + CommonUtilities::Vector2f(0.5, 0.5));

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

#pragma region Keyboard Input
	if (IsometricInput::GetKeyPressed(DIK_TAB) == true)
	{
		SelectPlayer();
	}
	if (IsometricInput::GetKeyPressed(DIK_P) == true)
	{
		if (mySelectedPlayer->GetMyAP() >= mySelectedPlayer->GetPeekCost())
		{
			CU::Vector2ui peekPosition;
			if (CheckIfCloseToDoor(CU::Vector2ui(mySelectedPlayer->GetPosition()), CU::Vector2ui(mySelectedPlayer->GetPreviousPosition()), peekPosition) == true)
			{
				CreatePlayerFoV(CU::Vector2f(peekPosition), 50);
				mySelectedPlayer->CostAP(mySelectedPlayer->GetPeekCost());
			}
		}
	}
#pragma endregion

#pragma region Mouse Input
	if (myMouseInput.GetMouseButtonPressed(CU::enumMouseButtons::eLeft) == true)
	{
		int AdditinoalAPCost = 0;
		enumMouseState currentState = GetCurrentMouseState();
		switch (currentState)
		{
		case enumMouseState::eClickedOnPlayer:
			SelectPlayer();
			break;
		case enumMouseState::eClickedOnEnemy:
			AdditinoalAPCost = GetPlayerAttackAPCost() ;
		case enumMouseState::eClickedOnEmptyTile:
		{
			PathArray positionPath;
			BuildPath(positionPath);

			

			if (GetPlayerAP() >= (positionPath.Size() - 1) + AdditinoalAPCost)
			{
				CostAP(positionPath.Size() - 1 + AdditinoalAPCost);
				NotifyPlayers(positionPath);
				SendPostMessage(NavigationClearMessage(RecieverTypes::eRoom));
			}
		}
			break;
		case enumMouseState::enumLength:
			DL_ASSERT(false, "Error in handling playercontroller mouse input");
		case enumMouseState::eClickedOnVoid:
			break;
		}
	}
#pragma  endregion

}

enumMouseState PlayerController::GetCurrentMouseState()
{
	const TilePosition mousePosition = TilePosition(IsometricInput::GetMouseWindowPositionIsometric() + CommonUtilities::Vector2f(0.5, 0.5));

	myClickedOnPlayer = false;
	myClickedOnEnemy = false;

	PointCollider tempCollider;

	tempCollider.ChangePosition(IsometricInput::GetMouseWindowPositionIsometric());

	SendPostMessage(ColliderMessage(RecieverTypes::eMouseClicked, tempCollider));

	if (myClickedOnPlayer == true)
	{
		return enumMouseState::eClickedOnPlayer;
	}
	else if (myClickedOnEnemy == true)
	{
		return enumMouseState::eClickedOnEnemy;
	}
	else if (myFloor->GetTile(mousePosition).CheckIfWalkable() == false || myFloor->GetTile(mousePosition).GetVertexHandle()->IsSearched() == false)
	{
		return enumMouseState::eClickedOnVoid;
	}
	else if (myFloor->GetTile(mousePosition).GetVertexHandle()->IsSearched() == true)
	{
		return enumMouseState::eClickedOnEmptyTile;
	}

	return enumMouseState::enumLength;
}

void PlayerController::ConstantUpdate(const CommonUtilities::Time& aDeltaTime)
{
	/*for (size_t i = 0; i < myDebugEnd.size(); i++)
	{
		DRAWISOMETRICLINE(myDebugStart[i], myDebugEnd[i]);
	}*/
	/*DL_PRINT("----------");
	for (size_t i = 0; i < myFloor->GetTile(myPlayers[0]->GetPosition().x, myPlayers[0]->GetPosition().y).GetAvailableDirections().Size(); i++)
	{
		if (myFloor->GetTile(myPlayers[0]->GetPosition().x, myPlayers[0]->GetPosition().y).GetAvailableDirections()[i] == eDirection::NORTH)
		{
			DL_PRINT("NORTH");
		}
		if (myFloor->GetTile(myPlayers[0]->GetPosition().x, myPlayers[0]->GetPosition().y).GetAvailableDirections()[i] == eDirection::EAST)
		{
			DL_PRINT("EAST");
		}
		if (myFloor->GetTile(myPlayers[0]->GetPosition().x, myPlayers[0]->GetPosition().y).GetAvailableDirections()[i] == eDirection::SOUTH)
		{
			DL_PRINT("SOUTH");
		}
		if (myFloor->GetTile(myPlayers[0]->GetPosition().x, myPlayers[0]->GetPosition().y).GetAvailableDirections()[i] == eDirection::WEST)
		{
			DL_PRINT("WEST");
		}

		if (myFloor->GetTile(myPlayers[0]->GetPosition().x, myPlayers[0]->GetPosition().y).GetAvailableDirections()[i] == eDirection::NORTH_EAST)
		{
			DL_PRINT("NORTH_EAST");
		}
		if (myFloor->GetTile(myPlayers[0]->GetPosition().x, myPlayers[0]->GetPosition().y).GetAvailableDirections()[i] == eDirection::NORTH_WEST)
		{
			DL_PRINT("NORTH_WEST");
		}
		if (myFloor->GetTile(myPlayers[0]->GetPosition().x, myPlayers[0]->GetPosition().y).GetAvailableDirections()[i] == eDirection::SOUTH_EAST)
		{
			DL_PRINT("SOUTH_EAST");
		}
		if (myFloor->GetTile(myPlayers[0]->GetPosition().x, myPlayers[0]->GetPosition().y).GetAvailableDirections()[i] == eDirection::SOUTH_WEST)
		{
			DL_PRINT("SOUTH_WEST");
		}
	}*/

}

void PlayerController::SetFloor(GameFloor & aFloor)
{
	myFloor = &aFloor;
}

void PlayerController::PrePlayer()
{
	SetCameraPositionToPlayer(mySelectedPlayerIndex);
	
	SendPostMessage(PlayerAPChangedMessage(RecieverTypes::ePlayerAPChanged, mySelectedPlayer->GetMyAP()));
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
	ResetTileShaders();
	for (size_t i = 0; i < myPlayers.Size(); i++)
	{
		if (myFloor->GetTile(myPlayers[i]->GetPosition().x, myPlayers[i]->GetPosition().y).GetTileType() == eTileType::DOOR)
		{
			CreatePlayerFoV(myPlayers[i]->GetPreviousPosition(), PlayerFoWRadius);
		}
		else
		{
			CreatePlayerFoV(myPlayers[i]->GetPosition(), PlayerFoWRadius);	
		}
		myPlayers[i]->AfterTurn();
	}
}

bool PlayerController::CheckForCandy(const TilePosition & aPosToCheckForCandyAt)
{
	return myFloor->GetTile(aPosToCheckForCandyAt).CheckHasCandy();
}

bool PlayerController::RecieveMessage(const GUIMessage & aMessage)
{
	if (aMessage.myType == RecieverTypes::eChangeSelectedPlayer)
	{
		const PlayerIDMessage * tempmessageerer = dynamic_cast<const PlayerIDMessage*>(&aMessage);
		RecieveMessage(*tempmessageerer);
	}
	return true;
}

void PlayerController::TakeCandy(const TilePosition & aPosToTakeCandyFrom)
{
	myScoreCounter.AddScore(enumScoreTypes::eCandy, 1.f);
	myFloor->GetTile(aPosToTakeCandyFrom).TakeCandy();
}

bool PlayerController::RecieveMessage(const PlayerIDMessage & aMessage)
{
	if (aMessage.myType == RecieverTypes::eChangeSelectedPlayer)
	{
		if (aMessage.myPlayerID != mySelectedPlayer->GetIndex())
		{
			SelectPlayer();
		}
	}

	else if (aMessage.myType == RecieverTypes::eClickedOnPlayer)
	{
		if (mySelectedPlayer->GetIndex() != aMessage.myPlayerID)
		{
			myClickedOnPlayer = true;
		}
	}
	return true;
}

bool PlayerController::RecieveMessage(const PlayerObjectMessage & aMessage)
{
	/*if (aMessage.myType == RecieverTypes::eChangeSelectedPlayer)
	{
		if (mySelectedPlayer != &aMessage.myPlayer)
		{
			myClickedOnPlayer = true;
		}
	}*/
	if (aMessage.myType == RecieverTypes::ePlayerNextToObjective)
	{
		if (mySelectedPlayer->GetEnemyTarget() != USHRT_MAX && mySelectedPlayer->GetMyAP() >= mySelectedPlayer->GetAttackCost())
		{
			myScoreCounter.AddScore(enumScoreTypes::eEnemiesKilled, 1);
			ActivePlayerFight(aMessage.myPlayer.GetIndex());
			mySelectedPlayer->CostAP(mySelectedPlayer->GetAttackCost());
		}
	}
	else if (aMessage.myType == RecieverTypes::ePlayerReachedEndOfPath)
	{
		CU::Vector2ui peekPosition;
		if (CheckIfCloseToDoor(CU::Vector2ui(mySelectedPlayer->GetTargetPosition()), CU::Vector2ui(mySelectedPlayer->GetPreviousPosition()), peekPosition) == true)
		{
			SendPostMessage(PlayerCanPeekMessage(RecieverTypes::ePlayerCanPeek, peekPosition, *mySelectedPlayer));
			DL_PRINT("Can Peek");
		}
	}

	return true;
}

bool PlayerController::RecieveMessage(const PlayerPositionChangedMessage& aMessage)
{
	myDebugStart.clear();
	myDebugEnd.clear();
	for (unsigned short iPlayer = 0; iPlayer < myPlayers.Size(); iPlayer++)
	{
		if (&aMessage.myPlayer != myPlayers[iPlayer])
		{
			CreatePlayerFoV(CU::Vector2f(myPlayers[iPlayer]->GetPosition()), PlayerFoWRadius);
			break;
		}
	}
	CreatePlayerFoV(CU::Vector2f(aMessage.myPosition), PlayerFoWRadius);


	if (CheckForCandy(aMessage.myPosition) == true)
	{
		TakeCandy(aMessage.myPosition);
	}

	if (myFloor->GetTile(CommonUtilities::Vector2ui(aMessage.myPlayer.GetPosition())).GetTileType() == eTileType::IS_OBJECTIVE)
	{
		SendPostMessage(PositionMessage(RecieverTypes::eLeaveObjective, CommonUtilities::Vector2i(aMessage.myPlayer.GetPosition())));
	}

	if (myFloor->GetTile(aMessage.myPosition.x, aMessage.myPosition.y).GetTileType() == eTileType::IS_OBJECTIVE == true)
	{
		SendPostMessage(PositionMessage(RecieverTypes::eObjctive, CommonUtilities::Vector2i(aMessage.myPosition)));
		DL_PRINT("You have reached the goal, Aren't you special");
	}

	

	return true;
}

bool PlayerController::RecieveMessage(const PlayerAddedMessage& aMessage)
{
	ResetTileShaders();
	for (unsigned short iPlayer = 0; iPlayer < myPlayers.Size(); iPlayer++)
	{
		CreatePlayerFoV(myPlayers[iPlayer]->GetPosition(), PlayerFoWRadius);
	}
	return true;
}

bool PlayerController::RecieveMessage(const EnemyObjectMessage & aMessage)
{
	myClickedOnEnemy = true;
	mySelectedPlayer->SetTargetEnemy(aMessage.myEnemy.GetIndex(), aMessage.myEnemy.GetPosition());
	if (aMessage.myType == RecieverTypes::eEnemyAttacked)
	{
		mySelectedPlayer->SetActiveState(false);
		for (size_t i = 0; i < myPlayers.Size(); i++)
		{
			if (myPlayers[i]->GetActorState() == eActorState::eAlert)
			{
				myPlayers[i]->SetActorState(eActorState::eIdle);
			}
		}
	}
	if (aMessage.myType == RecieverTypes::eEnemyDead)
	{
		mySelectedPlayer->SetActiveState(true);
	}
	return true;
}

void PlayerController::PlayerSeen(CommonUtilities::Point2i aPlayerPosition, Enemy* aEnemy)
{
	SendPostMessage(PlayerSeenMessage(RecieverTypes::ePlayEvents, aPlayerPosition, *aEnemy));
	myAlertSound->Play(0.3f);
}

bool PlayerController::RecieveMessage(const EnemyPositionChangedMessage& aMessage)
{
	for (unsigned short iPlayer = 0; iPlayer < myPlayers.Size(); iPlayer++)
	{
		switch (mySelectedPlayer->GetDirectionEnum())
		{
		case eDirection::NORTH:
		case eDirection::NORTH_EAST:
		case eDirection::WEST:
		case eDirection::NORTH_WEST:
			if (myFloor->GetTile(CU::Vector2ui(USHORTCAST(round(myPlayers[iPlayer]->GetPosition().x + 0.49f)), USHORTCAST(round(myPlayers[iPlayer]->GetPosition().y + 0.49f)))).GetInEnemyFov() == true)
			{
				PlayerSeen(CommonUtilities::Point2i(myPlayers[iPlayer]->GetPosition()), myFloor->GetTile(CU::Vector2ui(USHORTCAST(myPlayers[iPlayer]->GetPosition().x), USHORTCAST(myPlayers[iPlayer]->GetPosition().y))).GetSeenEnemy());
			}
			break;
		case eDirection::SOUTH_WEST:
		case eDirection::EAST:
		case eDirection::SOUTH:
		case eDirection::SOUTH_EAST:
		if (myFloor->GetTile(CU::Vector2ui(USHORTCAST(myPlayers[iPlayer]->GetPosition().x), USHORTCAST(myPlayers[iPlayer]->GetPosition().y))).GetInEnemyFov() == true)
		{
			PlayerSeen(CommonUtilities::Point2i(myPlayers[iPlayer]->GetPosition()), myFloor->GetTile(CU::Vector2ui(USHORTCAST(myPlayers[iPlayer]->GetPosition().x), USHORTCAST(myPlayers[iPlayer]->GetPosition().y))).GetSeenEnemy());
		}
			break;
		default:
			break;
		}
		
	}
	return true;
}

bool PlayerController::RecieveMessage(const EnemyDirectionChangedMessage& aMessage)
{
	for (unsigned short iPlayer = 0; iPlayer < myPlayers.Size(); iPlayer++)
	{
		if (myFloor->GetTile(CU::Vector2ui(USHORTCAST(myPlayers[iPlayer]->GetPosition().x), USHORTCAST(myPlayers[iPlayer]->GetPosition().y))).GetInEnemyFov() == true)
		{
			
			PlayerSeen(CommonUtilities::Point2i(myPlayers[iPlayer]->GetPosition()), myFloor->GetTile(CU::Vector2ui(USHORTCAST(myPlayers[iPlayer]->GetPosition().x), USHORTCAST(myPlayers[iPlayer]->GetPosition().y))).GetSeenEnemy());
		}
	}
	return false;
}

void PlayerController::ActivePlayerFight(const unsigned short aPlayerIndex)
{
	SendPostMessage(FightWithEnemyMessage(RecieverTypes::eStartFight, myPlayers[aPlayerIndex]->GetEnemyTarget()));
	myPlayers[aPlayerIndex]->ResetObjectiveState();
}

bool PlayerController::CheckIfCloseToDoor(const CU::Vector2ui &aPosition, const CU::Vector2ui &aOldPosition, CU::Vector2ui &aPeekLocation) const
{
#pragma region Check if player is on the door
	if (myFloor->GetTile(USHORTCAST(aPosition.x ), USHORTCAST(aPosition.y)).GetTileType() == eTileType::DOOR ||
		myFloor->GetTile(USHORTCAST(aPosition.x), USHORTCAST(aPosition.y)).GetTileType() == eTileType::DOOR_2)
	{
#pragma region Check from which room the player came from(diagonal)
	if (static_cast<int>(aOldPosition.x - aPosition.x) > 0 && static_cast<int>(aOldPosition.y - aPosition.y) > 0)
	{
		aPeekLocation = aPosition + CU::Vector2ui(-1, 0);
		if (myFloor->GetTile(aPeekLocation.x, aPeekLocation.y).GetTileType() == eTileType::BLOCKED)
		{
			aPeekLocation = aPosition + CU::Vector2ui(0, -1);
		}
	}
	else if (static_cast<int>(aOldPosition.x - aPosition.x) > 0 && static_cast<int>(aOldPosition.y - aPosition.y) < 0)
	{
		aPeekLocation = aPosition + CU::Vector2ui(-1, 0);
		if (myFloor->GetTile(aPeekLocation.x, aPeekLocation.y).GetTileType() == eTileType::BLOCKED)
		{
			aPeekLocation = aPosition + CU::Vector2ui(0, 1);
		}
	}
	else if (static_cast<int>(aOldPosition.x - aPosition.x) < 0 && static_cast<int>(aOldPosition.y - aPosition.y) > 0)
	{
		aPeekLocation = aPosition + CU::Vector2ui(1, 0);
		if (myFloor->GetTile(aPeekLocation.x, aPeekLocation.y).GetTileType() == eTileType::BLOCKED)
		{
			aPeekLocation = aPosition + CU::Vector2ui(0, -1);
		}
	}
	else if (static_cast<int>(aOldPosition.x - aPosition.x) < 0 && static_cast<int>(aOldPosition.y - aPosition.y) > 0)
	{
		aPeekLocation = aPosition + CU::Vector2ui(1, 0);
		if (myFloor->GetTile(aPeekLocation.x, aPeekLocation.y).GetTileType() == eTileType::BLOCKED)
		{
			aPeekLocation = aPosition + CU::Vector2ui(0, 1);
		}
	}
	else if (static_cast<int>(aOldPosition.x - aPosition.x) < 0 && static_cast<int>(aOldPosition.y - aPosition.y) < 0)
	{
		aPeekLocation = aPosition + CU::Vector2ui(1, 0);
		if (myFloor->GetTile(aPeekLocation.x, aPeekLocation.y).GetTileType() == eTileType::BLOCKED)
		{
			aPeekLocation = aPosition + CU::Vector2ui(0, 1);
		}
	}
#pragma endregion 
#pragma region Check from which room the player came from(straight)
		else if (static_cast<int>(aOldPosition.y - aPosition.y) > 0)
		{
			aPeekLocation = aPosition + CU::Vector2ui(0, -1);
		}
		else if (static_cast<int>(aOldPosition.y - aPosition.y) < 0)
		{
			aPeekLocation = aPosition + CU::Vector2ui(0, 1);
		}
		else if (static_cast<int>(aOldPosition.x - aPosition.x) > 0)
		{
			aPeekLocation = aPosition + CU::Vector2ui(-1, 0);
		}
		else if (static_cast<int>(aOldPosition.x - aPosition.x) < 0)
		{
			aPeekLocation = aPosition + CU::Vector2ui(1, 0);
		}
#pragma endregion 

		return true;
	}
#pragma endregion

#pragma region Check if player is standing on tile that is diagonal from the door
	if (myFloor->GetTile(USHORTCAST(aPosition.x + 1.f), USHORTCAST(aPosition.y - 1.f)).GetTileType() == eTileType::DOOR ||
		myFloor->GetTile(USHORTCAST(aPosition.x + 1.f), USHORTCAST(aPosition.y - 1.f)).GetTileType() == eTileType::DOOR_2)
	{
		aPeekLocation = aPosition + CU::Vector2ui(2, -1);
		if (myFloor->GetTile(aPeekLocation.x, aPeekLocation.y).GetTileType() == eTileType::BLOCKED)
		{
			aPeekLocation = aPosition + CU::Vector2ui(1, -2);
		}
		return true;
	}
	if (myFloor->GetTile(USHORTCAST(aPosition.x + 1.f), USHORTCAST(aPosition.y + 1.f)).GetTileType() == eTileType::DOOR ||
		myFloor->GetTile(USHORTCAST(aPosition.x + 1.f), USHORTCAST(aPosition.y + 1.f)).GetTileType() == eTileType::DOOR_2)
	{
		aPeekLocation = aPosition + CU::Vector2ui(2, 1);
		if (myFloor->GetTile(aPeekLocation.x, aPeekLocation.y).GetTileType() == eTileType::BLOCKED)
		{
			aPeekLocation = aPosition + CU::Vector2ui(1, 2);
		}
		return true;
	}
	if (myFloor->GetTile(USHORTCAST(aPosition.x - 1.f), USHORTCAST(aPosition.y - 1.f)).GetTileType() == eTileType::DOOR || 
		myFloor->GetTile(USHORTCAST(aPosition.x - 1.f), USHORTCAST(aPosition.y - 1.f)).GetTileType() == eTileType::DOOR_2)
	{
		aPeekLocation = aPosition + CU::Vector2ui(-2, -1);
		if (myFloor->GetTile(aPeekLocation.x, aPeekLocation.y).GetTileType() == eTileType::BLOCKED)
		{
			aPeekLocation = aPosition + CU::Vector2ui(-1, -2);
		}
		return true;
	}
	if (myFloor->GetTile(USHORTCAST(aPosition.x - 1.f), USHORTCAST(aPosition.y + 1.f)).GetTileType() == eTileType::DOOR || 
		myFloor->GetTile(USHORTCAST(aPosition.x - 1.f), USHORTCAST(aPosition.y + 1.f)).GetTileType() == eTileType::DOOR_2)
	{
		aPeekLocation = aPosition + CU::Vector2ui(-2, 1);
		if (myFloor->GetTile(aPeekLocation.x, aPeekLocation.y).GetTileType() == eTileType::BLOCKED)
		{
			aPeekLocation = aPosition + CU::Vector2ui(-1, 2);
		}
		return true;
	}
#pragma endregion

#pragma region Check if player is standing on tile that is straight from the door
	if (myFloor->GetTile(USHORTCAST(aPosition.x + 1.f), USHORTCAST(aPosition.y)).GetTileType() == eTileType::DOOR ||
		myFloor->GetTile(USHORTCAST(aPosition.x + 1.f), USHORTCAST(aPosition.y)).GetTileType() == eTileType::DOOR_2)
	{
		aPeekLocation = aPosition + CU::Vector2ui(2, 0);
		return true;
	}
	if (myFloor->GetTile(USHORTCAST(aPosition.x - 1.f), USHORTCAST(aPosition.y)).GetTileType() == eTileType::DOOR ||
		myFloor->GetTile(USHORTCAST(aPosition.x - 1.f), USHORTCAST(aPosition.y)).GetTileType() == eTileType::DOOR_2)
	{
		aPeekLocation = aPosition + CU::Vector2ui(-2, 0);
		return true;
	}
	if (myFloor->GetTile(USHORTCAST(aPosition.x ), USHORTCAST(aPosition.y - 1.f)).GetTileType() == eTileType::DOOR ||
		myFloor->GetTile(USHORTCAST(aPosition.x), USHORTCAST(aPosition.y - 1.f)).GetTileType() == eTileType::DOOR_2)
	{
		aPeekLocation = aPosition + CU::Vector2ui(0, -2);
		return true;
	}
	if (myFloor->GetTile(USHORTCAST(aPosition.x), USHORTCAST(aPosition.y + 1.f)).GetTileType() == eTileType::DOOR ||
		myFloor->GetTile(USHORTCAST(aPosition.x), USHORTCAST(aPosition.y + 1.f)).GetTileType() == eTileType::DOOR_2)
	{
		aPeekLocation = aPosition + CU::Vector2ui(0, 2);
		return true;
	}
#pragma endregion
	return false;	
}

void PlayerController::BuildPath(PathArray & aPathContainterToBuild)
{
	const TilePosition mousePosition = TilePosition(IsometricInput::GetMouseWindowPositionIsometric() + CommonUtilities::Vector2f(0.5, 0.5));

	CommonUtilities::GrowingArray<int> indexPath = myFloor->GetTile(mousePosition).GetVertexHandle()->GetPath();

	aPathContainterToBuild.Init(indexPath.Size());

	for (size_t i = 0; i < indexPath.Size(); i++)
	{
		aPathContainterToBuild.Add(CommonUtilities::Vector2ui(myFloor->GetTile(indexPath[indexPath.Size() - (i + 1)]).GetPosition()));
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
		if (hasAlreadyBeenBlocked == true && myFloor->GetTile(x, y).GetTileType() == eTileType::BLOCKED || myFloor->GetTile(x, y).GetTileType() == eTileType::DOOR)
		{
			myFloor->GetTile(x, y).SetVisible(true);
			myFloor->GetTile(x, y).SetDiscovered(true);
			break;
		}
		if (hasAlreadyBeenBlocked == true && myFloor->GetTile(x, y).GetTileType() != eTileType::BLOCKED || myFloor->GetTile(x, y).GetTileType() == eTileType::DOOR)
		{
			break;
		}
		if (myFloor->GetTile(x, y).GetTileType() == eTileType::BLOCKED)
		{
			myFloor->GetTile(x, y).SetVisible(true);
			myFloor->GetTile(x, y).SetDiscovered(true);
			hasAlreadyBeenBlocked = true;
		}
		myFloor->GetTile(x, y).SetVisible(true);
		myFloor->GetTile(x, y).SetDiscovered(true);
		
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
	
void PlayerController::CalculateCircleRayTrace(const TilePositionf & aPosition, const TilePositionf & aPlayerPosition)
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

int PlayerController::GetPlayerAttackAPCost() const
{
	return mySelectedPlayer->GetAttackCost();
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
		//myFloor->GetTile(i).SetDiscovered(false);
	}
}
