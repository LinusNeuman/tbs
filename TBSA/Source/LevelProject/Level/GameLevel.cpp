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

#include <Message/SetMainCameraMessage.h>
#include <CU/Matriser/matrix.h>
#include <CU/Intersection/Shapes2D/LineSegment2D.h>
#include <Message/EndTurnMessage.h>

const float sqrt2 = static_cast<float>(sqrt(2));

GameLevel::GameLevel()
{
}


GameLevel::~GameLevel()
{
}

void GameLevel::Init(const std::string& aLevelPath)
{
	Shaders::Create();
	myFloor.Init(100);

	SingletonPostMaster::AddReciever(RecieverTypes::eRoom, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eTurn, myTurnManager);

	TiledLoader::Load("Data/Tiled/SecondTest.json", myTiledData);
	SingletonPostMaster::PostMessage(LevelTileMetricsMessage(RecieverTypes::eLevelTileLayoutSettings, myTiledData.myMapSize));


	myFloor.SetTiles(myTiledData.myTiles);
	myFloor.SetFloorDimensions(myTiledData.myMapSize);

	myPlayerFactory.LoadFromJson();
	myEnemyFactory.LoadFromJson();

	ConstructNavGraph();

	myPlayerController = &myTurnManager.GetPlayerController();
	myEnemyController = &myTurnManager.GetEnemyController();
	myPlayerController->Init();
	myPlayerController->SetFloor(myFloor);

	myPlayer = myPlayerFactory.CreatePlayer(eActorType::ePlayerOne);
	myPlayer2 = myPlayerFactory.CreatePlayer(eActorType::ePlayerTwo);
	myPlayerController->AddPlayer(myPlayer);
	myPlayerController->AddPlayer(myPlayer2);
	myEnemy = myEnemyFactory.CreateEnemy(eActorType::eEnemyOne);
	myEnemyController->AddEnemy(myEnemy);

	CommonUtilities::GrowingArray<CommonUtilities::Point2ui> path;
	path.Init(5);

	for (size_t i = 0; i < 5; i++)
	{
		path.Add(CommonUtilities::Vector2ui(myEnemy->GetPosition()) + CommonUtilities::Vector2ui(i, 0));
	}
	myEnemy->SetEnemyPath(path);

	myPlayer->ChangeAnimation("PlayerTurn");
	myPlayer2->ChangeAnimation("PlayerTurn");
	myEnemy->ChangeAnimation("EnemyTurn");

	DX2D::CCustomShader* customShader;
	DX2D::CCustomShader* customFoVShader;
	customShader = new DX2D::CCustomShader();
	customFoVShader = new DX2D::CCustomShader();
	customShader->SetTextureAtRegister(DX2D::CEngine::GetInstance()->GetTextureManager().GetTexture("Sprites/Players/Player2/characterSheetTurnaround2.png"), DX2D::EShaderTextureSlot_1); // Add a texture
	customShader->SetShaderdataFloat4(DX2D::Vector4f(myPlayer->GetPosition().x, myPlayer->GetPosition().y, 1.f, 1.f), DX2D::EShaderDataID_1);
	customFoVShader->SetShaderdataFloat4(DX2D::Vector4f(myPlayer->GetPosition().x, myPlayer->GetPosition().y, 1.f, 1.f), DX2D::EShaderDataID_1);

	customShader->PostInit("shaders/custom_sprite_vertex_shader.fx", "shaders/custom_sprite_pixel_shader.fx", DX2D::EShaderDataBufferIndex_1);
	customFoVShader->PostInit("shaders/custom_sprite_vertex_shader.fx", "shaders/customLos_sprite_pixel_shader.fx", DX2D::EShaderDataBufferIndex_1);
	Shaders::GetInstance()->AddShader(customShader, "testShader");
	Shaders::GetInstance()->AddShader(customFoVShader, "FieldOfViewShader");

}

void GameLevel::Update(const CU::Time & aTimeDelta)
{
	static int index = 0;
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

	myTurnManager.Update(aTimeDelta);

	if (IsometricInput::GetKeyPressed(DIK_RETURN) == true)
	{
		SingletonPostMaster::PostMessage(EndTurnMessage(RecieverTypes::eTurn));
	}



	if (IsometricInput::GetKeyPressed(DIK_F3))
	{
		myFloor.CallFunctionOnAllTiles(std::mem_fn(&IsometricTile::ToggleDebugMode));
	}
	if (IsometricInput::GetKeyPressed(DIK_F4))
	{
		index += 25;
	}

	myPlayer->Update(aTimeDelta);
	myPlayer2->Update(aTimeDelta);
	myEnemy->Update(aTimeDelta);

	myDebugStart.clear();
	myDebugEnd.clear();

	ResetFoV();
	CreateEnemyRayTrace(index, 45.f, 4.f);
	CreatePlayerFoV(myPlayer->GetPosition(), 5.f);
	CreatePlayerFoV(myPlayer2->GetPosition(), 5.f);
	if (index > 100)
		index = 0;


	for (unsigned int i = 0; i < myFloor.Size(); i++)
	{
		for (unsigned int j = 0; j < myFloor.GetTile(i).myGraphicsLayers.Size(); j++)
		{
			if (myFloor.GetTile(i).GetVisible() == false)
			{
				myFloor.GetTile(i).myGraphicsLayers[j]->SetShader(Shaders::GetInstance()->GetShader("testShader")->myShader);
			}
			else if (myFloor.GetTile(i).GetInEnemyFov() == true && myFloor.GetTile(i).GetVisible() == true)
			{
				myFloor.GetTile(i).myGraphicsLayers[j]->SetShader(Shaders::GetInstance()->GetShader("FieldOfViewShader")->myShader);
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
	myEnemy->Draw();
	/*for (size_t i = 0; i < myDebugStart.size(); i++)
	{
	DRAWISOMETRICLINE(myDebugStart[i], myDebugEnd[i]);
	}*/
}

void GameLevel::RecieveMessage(const DijkstraMessage& aMessage)
{
	const CommonUtilities::Vector2ui position = aMessage.myPosition;
	const int distance = aMessage.myDistance;

	const CommonUtilities::Vector2ui mapSize = myTiledData.myMapSize;
	const int id = mapSize.x * position.y + position.x;

	const IsometricTile selectedTile = myFloor.GetTile(id);

	myNavGraph.Dijkstra(selectedTile.GetVertexHandle(), distance);
}

void GameLevel::RecieveMessage(const NavigationClearMessage& aMessage)
{
	myNavGraph.Clear();
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

		const int northWest = i - myTiledData.myMapSize.x - 1;
		if (northWest > -1 && myFloor.GetTile(northWest).GetVertexHandle().Null() == false)
		{
			EdgeHandle currentEdge = myNavGraph.CreateEdge();
			currentEdge->Setcost(1.1f);
			myFloor.GetTile(i).GetVertexHandle()->AddLink(currentEdge, myFloor.GetTile(northWest).GetVertexHandle());
		}

		const int north = i - myTiledData.myMapSize.x;
		if (north > -1 && myFloor.GetTile(north).GetVertexHandle().Null() == false)
		{
			EdgeHandle currentEdge = myNavGraph.CreateEdge();
			myFloor.GetTile(i).GetVertexHandle()->AddLink(currentEdge, myFloor.GetTile(north).GetVertexHandle());
		}

		const int northEast = i - myTiledData.myMapSize.x + 1;
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

void GameLevel::RayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition, bool aIsPlayer)
{
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
		if (myFloor.GetTile(x, y).GetTileType() == eTileType::BLOCKED)
		{
			break;
		}
		if (aIsPlayer == true)
		{
			myFloor.GetTile(x, y).SetVisible(true);
		}
		else
		{
			myFloor.GetTile(x, y).SetInEnemyFoV(true);
		}
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

void GameLevel::CreateEnemyRayTrace(int aIndex, float aAngle, float aMagnitude)
{
	//Will be replaced when enemies has a direction

	if (aIndex < 25)
	{
		CalculateFoVBasedOnAngle(CU::Vector2f(0, 1), aAngle, aMagnitude);
	}
	else if (aIndex < 50)
	{
		CalculateFoVBasedOnAngle(CU::Vector2f(1, 0), aAngle, aMagnitude);
	}
	else if (aIndex < 75)
	{
		CalculateFoVBasedOnAngle(CU::Vector2f(0, -1), aAngle, aMagnitude);
	}
	else
	{
		CalculateFoVBasedOnAngle(CU::Vector2f(-1, 0), aAngle, aMagnitude);
	}
}

void GameLevel::CalculateFoVBasedOnAngle(const CU::Vector2f &aShouldBeEnemyDirection, float aAngleInDegrees, float aMagnitude)
{
	float angle = abs((myEnemy->GetPosition() - myEnemy->GetPosition() + aShouldBeEnemyDirection).GetAngle() - abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 2.f)));
	float angle2 = abs((myEnemy->GetPosition() - myEnemy->GetPosition() + aShouldBeEnemyDirection).GetAngle() + abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 2.f)));
	float angle3 = abs((myEnemy->GetPosition() - myEnemy->GetPosition() + aShouldBeEnemyDirection).GetAngle() - abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 4.f)));
	float angle4 = abs((myEnemy->GetPosition() - myEnemy->GetPosition() + aShouldBeEnemyDirection).GetAngle() + abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 4.f)));
	float angle5 = abs((myEnemy->GetPosition() - myEnemy->GetPosition() + aShouldBeEnemyDirection).GetAngle());
	CU::Vector2f test = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle))));
	CU::Vector2f test3 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle3))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle3))));
	CU::Vector2f test2 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle2))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle2))));
	CU::Vector2f test4 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle4))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle4))));

	CU::Vector2f test5;
	//this should be alot less messy when enemies has directions, which would probably be with enums or something.

	if (aShouldBeEnemyDirection.x == 0 && aShouldBeEnemyDirection.y == 1)
	{
		test5 = CU::Vector2f(ceil(aMagnitude * cos(angle5)), ceil(aMagnitude * sin(angle5)));
	}
	else if (aShouldBeEnemyDirection.x == 1 && aShouldBeEnemyDirection.y == 0)
	{
		test5 = CU::Vector2f(ceil(aMagnitude * cos(angle5)), floor(aMagnitude * sin(angle5)));
	}
	else if (aShouldBeEnemyDirection.x == 0 && aShouldBeEnemyDirection.y == -1)
	{
		test5 = CU::Vector2f(floor(aMagnitude * cos(angle5)), ceil(aMagnitude * sin(angle5)));
	}
	else
	{
		test5 = CU::Vector2f(floor(aMagnitude * cos(angle5)), floor(aMagnitude * sin(angle5)));
	}

	RayTrace(myEnemy->GetPosition(), myEnemy->GetPosition() + test, false);
	RayTrace(myEnemy->GetPosition(), myEnemy->GetPosition() + test2, false);
	RayTrace(myEnemy->GetPosition(), myEnemy->GetPosition() + test3, false);
	RayTrace(myEnemy->GetPosition(), myEnemy->GetPosition() + test4, false);
	RayTrace(myEnemy->GetPosition(), myEnemy->GetPosition() + test5, false);
}

void GameLevel::CreatePlayerFoV(const CU::Vector2f& aPosition, float aRadius)
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

void GameLevel::CalculateCircleRayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& aPlayerPosition)
{
	RayTrace(aPlayerPosition, CU::Vector2f(aPosition.x + aPlayerPosition.x, aPosition.y + aPlayerPosition.y), true);
	RayTrace(aPlayerPosition, CU::Vector2f(-aPosition.x + aPlayerPosition.x, aPosition.y + aPlayerPosition.y), true);
	RayTrace(aPlayerPosition, CU::Vector2f(aPosition.x + aPlayerPosition.x, -aPosition.y + aPlayerPosition.y), true);
	RayTrace(aPlayerPosition, CU::Vector2f(-aPosition.x + aPlayerPosition.x, -aPosition.y + aPlayerPosition.y), true);
	RayTrace(aPlayerPosition, CU::Vector2f(aPosition.y + aPlayerPosition.x, aPosition.x + aPlayerPosition.y), true);
	RayTrace(aPlayerPosition, CU::Vector2f(aPosition.y + aPlayerPosition.x, -aPosition.x + aPlayerPosition.y), true);
	RayTrace(aPlayerPosition, CU::Vector2f(-aPosition.y + aPlayerPosition.x, aPosition.x + aPlayerPosition.y), true);
	RayTrace(aPlayerPosition, CU::Vector2f(-aPosition.y + aPlayerPosition.x, -aPosition.x + aPlayerPosition.y), true);

}

void GameLevel::ResetFoV()
{
	for (unsigned int i = 0; i < myFloor.Size(); i++)
	{
		myFloor.GetTile(i).SetVisible(false);
		myFloor.GetTile(i).SetInEnemyFoV(false);
	}
}

int GameLevel::CalculatePoint(float aValue) const
{
	if (aValue <= 0)
	{
		return static_cast<int>(floor(aValue));
	}
	return static_cast<int>(ceil(aValue));
}
