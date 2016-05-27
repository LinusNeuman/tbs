#include "stdafx.h"
#include "PlayState.h"
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
//#include "tga2d\sprite\sprite.h"
#include <Shader/Shaders.h>

#include <TiledData/TiledData.h>
#include <Message/LevelTileMetricsMessage.h>
#include <PostMaster/SingletonPostMaster.h>
#include "../../PathFinding/NavGraph/NavHandle.h"
#include "../PathFinding/NavGraph/Vertex/NavVertex.h"
//#include "../PathFinding/NavGraph/Edge/NavEdge.h"
#include <input/SingletonIsometricInputWrapper.h>
#include <Message/DijkstraMessage.h>

#include <Message/SetMainCameraMessage.h>
#include <CU/Matriser/matrix.h>
#include <CU/Intersection/Shapes2D/LineSegment2D.h>

#define EDGE_SCROLL_LIMIT 0.05f

const float sqrt2 = static_cast<float>( sqrt(2));
const float CameraSpeed = 10.f;

PlayState::PlayState()
{
}


PlayState::~PlayState()
{
}

void PlayState::Init()
{
	Shaders::Create();
	myTiles.Init(100);
	
	

	SingletonPostMaster::AddReciever(RecieverTypes::eRoom, *this);
	
	TiledLoader::Load("Data/Tiled/SecondTest.json", myTiledData);
	SingletonPostMaster::PostMessage(LevelTileMetricsMessage(RecieverTypes::eLevelTileLayoutSettings, myTiledData.myMapSize));

	SendPostMessage(SetMainCameraMessage(RecieverTypes::eCamera, myCamera));

	myTiles = myTiledData.myTiles;
	myPlayerFactory.LoadFromJson();
	myEnemyFactory.LoadFromJson();
	
	ConstructNavGraph();

	myPlayerController = &myTurnManager.GetPlayerController();
	myPlayerController->SetMyPlayState(*this);
	myPlayer = myPlayerFactory.CreatePlayer(eActorType::ePlayerOne);
	myPlayer2 = myPlayerFactory.CreatePlayer(eActorType::ePlayerTwo);
	myPlayerController->AddPlayer(myPlayer);
	myPlayerController->AddPlayer(myPlayer2);
	myEnemy = myEnemyFactory.CreateEnemy(eActorType::eEnemyOne);
	myPlayerController->AddPlayer(myEnemy);
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

	//Shaders::GetInstance()->ApplyShader(myPlayer2->mySprite, "testShader");

}

eStackReturnValue PlayState::Update(const CU::Time & aTimeDelta, ProxyStateStack & /*aStateStack*/)
{
	//(aStateStack);
	static int index = 0;
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Update));

	const CommonUtilities::Vector2ui mousePosition = CommonUtilities::Vector2ui(IsometricInput::GetMouseWindowPositionIsometric() + CommonUtilities::Vector2f(0.5,0.5));

	GetTile(mousePosition).SetTileState(eTileState::UNDER_MOUSE);

	if (GetTile(mousePosition).CheckIfWalkable() == true && GetTile(mousePosition).GetVertexHandle()->IsSearched() == true)
	{
		CommonUtilities::GrowingArray<int> path = GetTile(mousePosition).GetVertexHandle()->GetPath();
		for (size_t i = 0; i < path.Size(); i++)
		{
			myTiles[path[i]].SetTileState(eTileState::IN_PATH);
		}
	}

	myTurnManager.Update(aTimeDelta);
	/*if (IsometricInput::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft))
	{
		if (GetTile(mousePosition).CheckIfWalkable() == true && GetTile(mousePosition).GetVertexHandle()->IsSearched() == true)
		{
			CommonUtilities::GrowingArray<int> indexPath = GetTile(mousePosition).GetVertexHandle()->GetPath();
			CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> positionPath;
			positionPath.Init(indexPath.Size());

			for (size_t i = 0; i < indexPath.Size(); i++)
			{
				positionPath.Add(CommonUtilities::Vector2ui(myTiles[indexPath[indexPath.Size() - (i + 1)]].GetPosition()));
			}
			if (myPlayerController->GetPlayerAP() >= positionPath.Size())
			{
				myPlayerController->NotifyPlayers(positionPath);
				myNavGraph.Clear(); 
			}
		}

	}
	if (IsometricInput::GetKeyPressed(DIK_TAB) == true)
	{
		myPlayerController->SelectPlayer();
	}*/

	if (IsometricInput::GetKeyPressed(DIK_ESCAPE) == true)
	{
		return eStackReturnValue::ePopMain;
	}
	/*if (IsometricInput::GetKeyReleased(DIK_Q) == true)
	{
		bool isFalse = false;
		DL_ASSERT(isFalse, "IT Works!");
	}*/

	if (IsometricInput::GetKeyDown(DIK_W) || IsometricInput::GetMouseWindowPositionNormalizedSpace().y <= EDGE_SCROLL_LIMIT)
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(0.f, -CameraSpeed) * aTimeDelta.GetSeconds()));
	}
	if (IsometricInput::GetKeyDown(DIK_S) ||IsometricInput::GetMouseWindowPositionNormalizedSpace().y >= 1.f - EDGE_SCROLL_LIMIT)
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(0.f, CameraSpeed) * aTimeDelta.GetSeconds()));
	}
	if (IsometricInput::GetKeyDown(DIK_A) || IsometricInput::GetMouseWindowPositionNormalizedSpace().x <= EDGE_SCROLL_LIMIT)
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(-CameraSpeed, 0.0f) * aTimeDelta.GetSeconds()));
	}
	if (IsometricInput::GetKeyDown(DIK_D) || IsometricInput::GetMouseWindowPositionNormalizedSpace().x >= 1.f - EDGE_SCROLL_LIMIT)
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(CameraSpeed, 0.0f) * aTimeDelta.GetSeconds()));
	}

	if (IsometricInput::GetKeyPressed(DIK_F3))
	{
		myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::ToggleDebugMode));
	}
	if (IsometricInput::GetKeyPressed(DIK_F4))
	{
		index += 25;
	}

	/*CU::Vector2f testLine(IsometricInput::GetMouseWindowPosition());
	DRAWLINE(CU::Vector2f::Zero, testLine);
	DRAWLINE(CU::Vector2f(1920.f, 0.f), testLine);
	DRAWLINE(CU::Vector2f(1920.f, 1080.f), testLine);
	DRAWLINE(CU::Vector2f(0.f, 1080.f), testLine);*/

	/*CU::Vector2f testIsoLine(IsometricInput::GetMouseWindowPositionIsometric());
	DRAWISOMETRICLINE(CU::Vector2f::Zero, testIsoLine);
	DRAWISOMETRICLINE(CU::Vector2f(0.f, 10.f), testIsoLine);
	DRAWISOMETRICLINE(CU::Vector2f(20.f, 10.f), testIsoLine);
	DRAWISOMETRICLINE(CU::Vector2f(20.f, 0.f), testIsoLine);*/

	myPlayer->Update(aTimeDelta);
	myPlayer2->Update(aTimeDelta);
	myEnemy->Update(aTimeDelta);

	myDebugStart.clear();
	myDebugEnd.clear();
	CalculateRayTrace(index,45.f,4.f);
	if (index > 100)
		index = 0;
	return eStackReturnValue::eStay;
}

void PlayState::Draw() const
{
	for (unsigned int i = 0; i < myTiles.Size(); i++)
	{
		CU::Vector2f distance = myTiles[i].GetPosition() - myPlayer->GetPosition();
		for (unsigned int j = 0; j < myTiles[i].myGraphicsLayers.Size(); j++)
		{
			if (distance.Length2() > 36.0f)
			{
				myTiles[i].myGraphicsLayers[j]->SetShader(Shaders::GetInstance()->GetShader("testShader")->myShader);
			}
			else
			{
				myTiles[i].myGraphicsLayers[j]->SetShader(nullptr);
			}
		}
	}

	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Draw));
	myPlayer->Draw();
	myPlayer2->Draw();
	myEnemy->Draw();
	std::cout << IsometricInput::GetMouseWindowPositionIsometric().x << " " << IsometricInput::GetMouseWindowPositionIsometric().y << std::endl;
	for (size_t i = 0; i < myDebugStart.size(); i++)
	{
		DRAWISOMETRICLINE(myDebugStart[i], myDebugEnd[i]);
	}
}

void PlayState::RecieveMessage(const DijkstraMessage& aMessage)
{
	const CommonUtilities::Vector2ui position = aMessage.myPosition;
	const int distance = aMessage.myDistance;

	const CommonUtilities::Vector2ui mapSize = myTiledData.myMapSize;
	const int id = mapSize.x * position.y + position.x;

	const IsometricTile selectedTile = myTiles[id];

	myNavGraph.Dijkstra(selectedTile.GetVertexHandle(), distance);
}

void PlayState::RecieveMessage(const NavigationClearMessage& aMessage)
{
	myNavGraph.Clear();
}

void PlayState::ConstructNavGraph()
{
	for (size_t i = 0; i < myTiles.Size(); i++)
	{
		eTileType explainingType = myTiles[i].GetTileType();
		if (!(explainingType == eTileType::OPEN || explainingType == eTileType::DOOR|| explainingType == eTileType::DOOR_2))
		{
			continue;
		}

		VertexHandle currentHandle = myNavGraph.CreateVertex();
		myTiles[i].SetVertexHandle(currentHandle);
		currentHandle->SetAnyPurpouseId(static_cast<int>(i));

		//warning names of indexes may not coincide wwith where they are drawn
		//i.e north may not graphicly be drawn to the north of the current tile
		
		const int northWest = i - myTiledData.myMapSize.x - 1;
		if (northWest > -1 && myTiles[northWest].GetVertexHandle().Null() == false)
		{
			EdgeHandle currentEdge = myNavGraph.CreateEdge();
			currentEdge->Setcost(1.1f);
			myTiles[i].GetVertexHandle()->AddLink(currentEdge, myTiles[northWest].GetVertexHandle());
		}

		const int north = i - myTiledData.myMapSize.x;
		if (north > -1 && myTiles[north].GetVertexHandle().Null() == false)
		{
			EdgeHandle currentEdge = myNavGraph.CreateEdge();
			myTiles[i].GetVertexHandle()->AddLink(currentEdge, myTiles[north].GetVertexHandle());
		}

		const int northEast = i - myTiledData.myMapSize.x + 1;
		if (northEast > -1 && myTiles[northEast].GetVertexHandle().Null() == false)
		{
			EdgeHandle currentEdge = myNavGraph.CreateEdge();
			currentEdge->Setcost(1.1f);
			myTiles[i].GetVertexHandle()->AddLink(currentEdge, myTiles[northEast].GetVertexHandle());
		}

		const int west = i - 1;
		if (west > -1 && myTiles[west].GetVertexHandle().Null() == false)
		{
			EdgeHandle currentEdge = myNavGraph.CreateEdge();
			myTiles[i].GetVertexHandle()->AddLink(currentEdge, myTiles[west].GetVertexHandle());
		}
	}
}

IsometricTile& PlayState::GetTile(unsigned short aIndex)
{
	return  myTiles[aIndex];
}

void PlayState::RayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition)
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
		if (GetTile(x,y).GetTileType() == eTileType::BLOCKED)
		{
			break;
		}
		GetTile(x, y).SetTileState(eTileState::FIELD_OF_VIEW);		
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

void PlayState::CalculateRayTrace(int aIndex, float aAngle, float aMagnitude)
{
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

void PlayState::CalculateFoVBasedOnAngle(const CU::Vector2f &aShouldBeEnemyDirection, float aAngleInDegrees, float aMagnitude)
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
	
	RayTrace(myEnemy->GetPosition(), myEnemy->GetPosition() + test);
	RayTrace(myEnemy->GetPosition(), myEnemy->GetPosition() + test2);
	RayTrace(myEnemy->GetPosition(), myEnemy->GetPosition() + test3);
	RayTrace(myEnemy->GetPosition(), myEnemy->GetPosition() + test4);
	RayTrace(myEnemy->GetPosition(), myEnemy->GetPosition() + test5);
}

int PlayState::CalculatePoint(float aValue) const
{
	if (aValue <= 0)
	{
		return static_cast<int>(floor(aValue));
	}
	return static_cast<int>(ceil(aValue));
}