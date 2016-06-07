#include "stdafx.h"
#include "GameLevel.h"

#include <CU/Vectors/Vector2.h>
#include <Rend/StaticSprite.h>
#include <StateStack/ProxyStateStack.h>
#include <Rend/RenderConverter.h>
#include <GameObjects/Actor/Actor.h>
#include <Controllers/PlayerController.h>
#include <TiledLoader/TiledLoader.h>
#include <tga2d\shaders\customshader.h>
#include <tga2d\texture\texture_manager.h>
#include <tga2d\engine.h>
#include <Shader/Shaders.h>

#include <TiledData/TiledData.h>
#include <Message/LevelTileMetricsMessage.h>
#include <PostMaster/SingletonPostMaster.h>
#include <NavGraph/NavHandle.h>
#include <NavGraph/Vertex/NavVertex.h>
#include <input/SingletonIsometricInputWrapper.h>
#include <Message/DijkstraMessage.h>

#include <CU/Matriser/matrix.h>
#include <CU/Intersection/Shapes2D/LineSegment2D.h>
#include <Message/EndTurnMessage.h>
#include "../../GUI/GUI/Messaging/Generic/GUIMessage.h"

struct PlayerPositionChangedMessage;
const float sqrt2 = static_cast<float>(sqrt(2));

GameLevel::GameLevel()
{
}

GameLevel::~GameLevel()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eRoom, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eEndTurn, myTurnManager);
}

void GameLevel::Init(TiledData* aTileData)
{
	myTiledData = aTileData;

	myFloor.Init(100);

	SingletonPostMaster::AddReciever(RecieverTypes::eRoom, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eEndTurn, myTurnManager);

	SendPostMessage(LevelTileMetricsMessage(RecieverTypes::eLevelTileLayoutSettings, myTiledData->myMapSize));

	myFloor.SetTiles(myTiledData->myTiles);
	myFloor.SetFloorDimensions(myTiledData->myMapSize);

	ConstructNavGraph();

	myPlayerController = &myTurnManager.GetPlayerController();
	myEnemyController = &myTurnManager.GetEnemyController();
	myEnemyController->Init();
	myPlayerController->Init();
	myPlayerController->SetFloor(myFloor);
	myEnemyController->SetFloor(myFloor);

	myPlayer = myTiledData->myPlayers[0];
	myPlayer2 = myTiledData->myPlayers[1];
	myPlayerController->AddPlayer(myPlayer);
	myPlayerController->AddPlayer(myPlayer2);
	myEnemies = myTiledData->myEnemies;
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myEnemyController->AddEnemy(myEnemies[i]);
	}

	myObjectives = myTiledData->myObjectives;

	/*CommonUtilities::GrowingArray<CommonUtilities::Point2ui> path;
	path.Init(5);

	for (size_t i = 0; i < 5; i++)
	{
		path.Add(CommonUtilities::Vector2ui(myEnemies[0]->GetPosition()) + CommonUtilities::Vector2ui(i, 0));
	}
	myEnemies[0]->SetEnemyPath(path);*/

	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myEnemies[i]->ChangeAnimation("EnemyTurn");
	}

	myPlayerController->SetCameraPositionToPlayer(1);
	if (myObjectives.IsInitialized() == true)
	{
		for (size_t i = 0; i < myObjectives.Size(); i++)
		{
			myFloor.GetTile(CU::Vector2ui(USHORTCAST(myObjectives[i]->GetPosition().x), USHORTCAST(myObjectives[i]->GetPosition().y))).SetTileType(eTileType::IS_OBJECTIVE);
		}
	}	
	for (size_t y = 0; y < myFloor.GetDimensions().y; y++)
	{
		for (size_t x = 0; x < myFloor.GetDimensions().x; x++)
		{
			myFloor.GetTile(x, y).SetVisible(true);
			if (myFloor.GetTile(x,y).CheckIfWalkable() == false)
			{
				if (x + 1 < myFloor.GetDimensions().x && y + 1 < myFloor.GetDimensions().y &&
					x - 1 > 0 && y + 1 > 0)
				{
					myFloor.GetTile(x, y - 1).RemoveAvailableDirection(eDirection::NORTH);
					myFloor.GetTile(x, y - 1).RemoveAvailableDirection(eDirection::NORTH_EAST);
					myFloor.GetTile(x, y - 1).RemoveAvailableDirection(eDirection::NORTH_WEST);

					myFloor.GetTile(x + 1, y).RemoveAvailableDirection(eDirection::EAST);
					myFloor.GetTile(x + 1, y).RemoveAvailableDirection(eDirection::NORTH_EAST);
					myFloor.GetTile(x + 1, y).RemoveAvailableDirection(eDirection::SOUTH_WEST);

					myFloor.GetTile(x - 1, y).RemoveAvailableDirection(eDirection::WEST);
					myFloor.GetTile(x - 1, y).RemoveAvailableDirection(eDirection::NORTH_WEST);
					myFloor.GetTile(x - 1, y).RemoveAvailableDirection(eDirection::SOUTH_EAST);

					myFloor.GetTile(x, y + 1).RemoveAvailableDirection(eDirection::SOUTH);
					myFloor.GetTile(x, y + 1).RemoveAvailableDirection(eDirection::SOUTH_WEST);
					myFloor.GetTile(x, y + 1).RemoveAvailableDirection(eDirection::SOUTH_EAST);
				}
			}
		}
	}



}

void GameLevel::Update(const CU::Time & aTimeDelta)
{
	myFloor.Update();

	const CommonUtilities::Vector2ui mousePosition = CommonUtilities::Vector2ui(IsometricInput::GetMouseWindowPositionIsometric() + CommonUtilities::Vector2f(0.5, 0.5));

	myFloor.GetTile(mousePosition).SetTileState(eTileState::UNDER_MOUSE);

	if (myFloor.GetTile(mousePosition).CheckIfWalkable() == true && myFloor.GetTile(mousePosition).GetVertexHandle()->IsSearched() == true)
	{
		CommonUtilities::GrowingArray<int> path = myFloor.GetTile(mousePosition).GetVertexHandle()->GetPath();
		for (size_t i = 0; i < path.Size(); i++)
		{
			myFloor.GetTile(path[i]).SetTileState(eTileState::IN_PATH);
		}
	}

	myEnemyController->ConstantUpdate(aTimeDelta);
	myPlayerController->ConstantUpdate(aTimeDelta);
	if(myTurnManager.Update(aTimeDelta) == false)
	{
		return;
	}

	if (IsometricInput::GetKeyPressed(DIK_RETURN) == true)
	{
		SendPostMessage(GUIMessage(RecieverTypes::eEndTurn));
	}

	if (IsometricInput::GetKeyPressed(DIK_F3))
	{
		myFloor.CallFunctionOnAllTiles(std::mem_fn(&IsometricTile::ToggleDebugMode));
	}

	myPlayer->Update(aTimeDelta);
	myPlayer2->Update(aTimeDelta);


	for (unsigned int i = 0; i < myFloor.Size(); i++)
	{
		for (unsigned int j = 0; j < myFloor.GetTile(i).myGraphicsLayers.Size(); j++)
		{
			if (myFloor.GetTile(i).GetVisible() == false && myFloor.GetTile(i).GetTileState() != eTileState::IN_PATH)
			{
				myFloor.GetTile(i).myGraphicsLayers[j]->SetShader(Shaders::GetInstance()->GetShader("FogOfWarShader")->myShader);
			}
			else if (myFloor.GetTile(i).GetTileState() == eTileState::IN_PATH && myFloor.GetTile(i).GetInEnemyFov() == true && myFloor.GetTile(i).GetVisible() == true)
			{
				myFloor.GetTile(i).myGraphicsLayers[j]->SetShader(Shaders::GetInstance()->GetShader("HighlightRedShader")->myShader);
			}
			else if (myFloor.GetTile(i).GetTileState() == eTileState::IN_PATH)
			{
				myFloor.GetTile(i).myGraphicsLayers[j]->SetShader(Shaders::GetInstance()->GetShader("HighlightShader")->myShader);
			}
			else if (myFloor.GetTile(i).GetInEnemyFov() == true && myFloor.GetTile(i).GetVisible() == true)
			{
				myFloor.GetTile(i).myGraphicsLayers[j]->SetShader(Shaders::GetInstance()->GetShader("FieldOfViewShader")->myShader);
			}
			else if (myFloor.GetTile(i).GetTileState() == eTileState::IN_RANGE)
			{
				myFloor.GetTile(i).myGraphicsLayers[j]->SetShader(Shaders::GetInstance()->GetShader("InRangeShader")->myShader);
			}
			else
			{
				myFloor.GetTile(i).myGraphicsLayers[j]->SetShader(nullptr);
			}
		}
	}
}

void GameLevel::Draw() const
{
	myFloor.Draw();
	myPlayer->Draw();
	myPlayer2->Draw();
	myEnemyController->Draw();
}

bool GameLevel::RecieveMessage(const DijkstraMessage& aMessage)
{
	const CommonUtilities::Vector2ui position = aMessage.myPosition;
	const int distance = aMessage.myDistance;

	const CommonUtilities::Vector2ui mapSize = myTiledData->myMapSize;
	const int id = mapSize.x * position.y + position.x;

	const IsometricTile selectedTile = myFloor.GetTile(id);

	myNavGraph.Dijkstra(selectedTile.GetVertexHandle(), distance);
	return true;
}

bool GameLevel::RecieveMessage(const NavigationClearMessage& aMessage)
{
	myNavGraph.Clear();
	return true;
}

void GameLevel::ConstructNavGraph()
{
	for (size_t i = 0; i < myFloor.Size(); i++)
	{
		

		eTileType explainingType = myFloor.GetTile(i).GetTileType();
		if (!(explainingType == eTileType::OPEN || explainingType == eTileType::DOOR || explainingType == eTileType::DOOR_2))
		{
			continue;
		}

		VertexHandle currentHandle = myNavGraph.CreateVertex();
		myFloor.GetTile(i).SetVertexHandle(currentHandle);
		currentHandle->SetAnyPurpouseId(static_cast<int>(i));

		//warning names of indexes may not coincide wwith where they are drawn
		//i.e north may not graphicly be drawn to the north of the current tile

		const int northWest = i - myTiledData->myMapSize.x - 1;
		if (northWest > -1 && myFloor.GetTile(northWest).GetVertexHandle().Null() == false)
		{
			EdgeHandle currentEdge = myNavGraph.CreateEdge();
			currentEdge->Setcost(1.1f);
			myFloor.GetTile(i).GetVertexHandle()->AddLink(currentEdge, myFloor.GetTile(northWest).GetVertexHandle());
		}

		const int north = i - myTiledData->myMapSize.x;
		if (north > -1 && myFloor.GetTile(north).GetVertexHandle().Null() == false)
		{
			EdgeHandle currentEdge = myNavGraph.CreateEdge();
			myFloor.GetTile(i).GetVertexHandle()->AddLink(currentEdge, myFloor.GetTile(north).GetVertexHandle());
		}

		const int northEast = i - myTiledData->myMapSize.x + 1;
		if (northEast > -1 && myFloor.GetTile(northEast).GetVertexHandle().Null() == false)
		{
			EdgeHandle currentEdge = myNavGraph.CreateEdge();
			currentEdge->Setcost(1.1f);
			myFloor.GetTile(i).GetVertexHandle()->AddLink(currentEdge, myFloor.GetTile(northEast).GetVertexHandle());
		}

		const int west = i - 1;
		if (west > -1 && myFloor.GetTile(west).GetVertexHandle().Null() == false)
		{
			EdgeHandle currentEdge = myNavGraph.CreateEdge();
			myFloor.GetTile(i).GetVertexHandle()->AddLink(currentEdge, myFloor.GetTile(west).GetVertexHandle());
		}
	}
}
