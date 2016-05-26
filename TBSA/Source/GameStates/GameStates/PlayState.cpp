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
#include "tga2d\sprite\sprite.h"
#include <Shader/Shaders.h>

#include <TiledData/TiledData.h>
#include <Message/LevelTileMetricsMessage.h>
#include <PostMaster/SingletonPostMaster.h>
#include "../../PathFinding/NavGraph/NavHandle.h"
#include "../PathFinding/NavGraph/Vertex/NavVertex.h"
//#include "../PathFinding/NavGraph/Edge/NavEdge.h"
#include <Message/DijkstraMessage.h>

#include <Message/SetMainCameraMessage.h>


const float sqrt2 = sqrt(2);
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

	SendMessage(SetMainCameraMessage(RecieverTypes::eCamera, myCamera));

	myTiles = myTiledData.myTiles;
	myPlayerFactory.LoadFromJson();
	myEnemyFactory.LoadFromJson();
	

	myPlayerController = new PlayerController();
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

	ConstructNavGraph();
}

eStackReturnValue PlayState::Update(const CU::Time & aTimeDelta, ProxyStateStack & /*aStateStack*/)
{
	//(aStateStack);

	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Update));

	const CommonUtilities::Vector2ui mousePosition = CommonUtilities::Vector2ui(IsometricInput::GetMouseWindowPositionIsometric() + CommonUtilities::Vector2f(1.5,1.5));

	GetTile(mousePosition).SetTileState(eTileState::UNDER_MOUSE);

	if (GetTile(mousePosition).CheckIfWalkable() == true && GetTile(mousePosition).GetVertexHandle()->IsSearched() == true)
	{
		CommonUtilities::GrowingArray<int> path = GetTile(mousePosition).GetVertexHandle()->GetPath();
		for (size_t i = 0; i < path.Size(); i++)
		{
			myTiles[path[i]].SetTileState(eTileState::IN_PATH);
		}
	}

	if (IsometricInput::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft))
	{
		//myPlayerController->NotifyPlayers();
		if (GetTile(mousePosition).GetVertexHandle()->IsSearched() == true)
		{
			CommonUtilities::GrowingArray<int> indexPath = GetTile(mousePosition).GetVertexHandle()->GetPath();
			CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> positionPath;
			positionPath.Init(indexPath.Size());

			for (size_t i = 0; i < indexPath.Size(); i++)
			{
				positionPath.Add(CommonUtilities::Vector2ui(myTiles[indexPath[indexPath.Size() - (i + 1)]].GetPosition()) - CommonUtilities::Vector2ui(1, 1));
			}

			myPlayerController->NotifyPlayers(positionPath);
		}

	}
	if (IsometricInput::GetKeyPressed(DIK_TAB) == true)
	{
		myPlayerController->SelectPlayer();
	}
	if (IsometricInput::GetKeyPressed(DIK_ESCAPE) == true)
	{
		return eStackReturnValue::ePopMain;
	}
	/*if (IsometricInput::GetKeyReleased(DIK_Q) == true)
	{
		bool isFalse = false;
		DL_ASSERT(isFalse, "IT Works!");
	}*/

	if (IsometricInput::GetKeyDown(DIK_W))
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(0.f, -CameraSpeed) * aTimeDelta.GetSeconds()));
	}
	if (IsometricInput::GetKeyDown(DIK_S))
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(0.f, CameraSpeed) * aTimeDelta.GetSeconds()));
	}
	if (IsometricInput::GetKeyDown(DIK_A))
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(-CameraSpeed, 0.0f) * aTimeDelta.GetSeconds()));
	}
	if (IsometricInput::GetKeyDown(DIK_D))
	{
		myCamera.MoveCameraIsomertic((CU::Vector2f(CameraSpeed, 0.0f) * aTimeDelta.GetSeconds()));
	}

	if (IsometricInput::GetKeyPressed(DIK_F3))
	{
		myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::ToggleDebugMode));
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

	CalculateFoV(myEnemy->GetPosition(), 3.f);

	return eStackReturnValue::eStay;
}

void PlayState::Draw() const
{
	for (unsigned int i = 0; i < myTiles.Size(); i++)
	{
		CU::Vector2f distance = myTiles[i].GetPosition() - myPlayer->GetPosition();
		for (unsigned int j = 0; j < myTiles[i].myGraphicsLayers.Size(); j++)
		{
			if (distance.Length2() > 16.0f)
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
	//std::cout << IsometricInput::GetMouseWindowPositionIsometric().x << " " << IsometricInput::GetMouseWindowPositionIsometric().y << std::endl;
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
			currentEdge->Setcost(sqrt2);
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
			currentEdge->Setcost(sqrt2);
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

void PlayState::RayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition)
{
	CU::Vector2f position = aPosition + CU::Vector2f(1, 1);
	CU::Vector2f secondPosition = anotherPosition + CU::Vector2f(1, 1);
	double x0, x1, y0, y1;
	x0 = position.x;
	y0 = position.y;
	x1 = secondPosition.x;
	y1 = secondPosition.y;
	myDebugStart.push_back(position - CU::Vector2f(1, 1));
	myDebugEnd.push_back(secondPosition - CU::Vector2f(1, 1));


	double dx = fabs(x1 - x0);
	double dy = fabs(y1 - y0);

	int x = int(floor(x0));
	int y = int(floor(y0));

	double dt_dx = 1.0 / dx;
	double dt_dy = 1.0 / dy;

	double t = 0;

	int n = 1;
	int x_inc, y_inc;
	double t_next_vertical, t_next_horizontal;

	if (dx == 0)
	{
		x_inc = 0;
		t_next_horizontal = dt_dx; // infinity
	}
	else if (x1 > x0)
	{
		x_inc = 1;
		n += int(floor(x1)) - x;
		t_next_horizontal = (floor(x0) + 1 - x0) * dt_dx;
	}
	else
	{
		x_inc = -1;
		n += x - int(floor(x1));
		t_next_horizontal = (x0 - floor(x0)) * dt_dx;
	}

	if (dy == 0)
	{
		y_inc = 0;
		t_next_vertical = dt_dy; // infinity
	}
	else if (y1 > y0)
	{
		y_inc = 1;
		n += int(floor(y1)) - y;
		t_next_vertical = (floor(y0) + 1 - y0) * dt_dy;
	}
	else
	{
		y_inc = -1;
		n += y - int(floor(y1));
		t_next_vertical = (y0 - floor(y0)) * dt_dy;
	}

	for (; n > 0; --n)
	{
		GetTile(x, y).SetTileState(eTileState::FIELD_OF_VIEW);

		if (t_next_vertical < t_next_horizontal)
		{
			y += y_inc;
			t = t_next_vertical;
			t_next_vertical += dt_dy;
		}
		else
		{
			x += x_inc;
			t = t_next_horizontal;
			t_next_horizontal += dt_dx;
		}

		//GetTile(x, y).SetTileState(eTileState::FIELD_OF_VIEW);
	}



		
}

void PlayState::CalculateRayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition)
{
	RayTrace(myEnemy->GetPosition(), CU::Vector2f(aPosition.x + anotherPosition.x, aPosition.y + anotherPosition.y));
	RayTrace(myEnemy->GetPosition(), CU::Vector2f(-aPosition.x + anotherPosition.x, aPosition.y + anotherPosition.y));
	RayTrace(myEnemy->GetPosition(), CU::Vector2f(aPosition.x + anotherPosition.x, -aPosition.y + anotherPosition.y));
	RayTrace(myEnemy->GetPosition(), CU::Vector2f(-aPosition.x + anotherPosition.x, -aPosition.y + anotherPosition.y));
	RayTrace(myEnemy->GetPosition(), CU::Vector2f(aPosition.y + anotherPosition.x, aPosition.x + anotherPosition.y));
	RayTrace(myEnemy->GetPosition(), CU::Vector2f(aPosition.y + anotherPosition.x, -aPosition.x + anotherPosition.y));
	RayTrace(myEnemy->GetPosition(), CU::Vector2f(-aPosition.y + anotherPosition.x, aPosition.x + anotherPosition.y));
	RayTrace(myEnemy->GetPosition(), CU::Vector2f(-aPosition.y + anotherPosition.x, -aPosition.x + anotherPosition.y));
}

void PlayState::CalculateFoV(const CU::Vector2f& aPosition, float aRadius)
{
	int r, xc, yc, pk, x, y;
	xc = aPosition.x;
	yc = aPosition.y;
	r = aRadius;
	pk = 3 - 2 * r;
	x = 0; y = r;
	CalculateRayTrace(CU::Vector2f(x, y), CU::Vector2f(xc, yc));
	while (x < y)
	{
		if (pk <= 0)
		{
			pk = pk + (4 * x) + 6;
			CalculateRayTrace(CU::Vector2f(++x, y), CU::Vector2f(xc, yc));
		}
		else
		{
			pk = pk + (4 * (x - y)) + 10;
			CalculateRayTrace(CU::Vector2f(++x, --y), CU::Vector2f(xc, yc));
		}
	}
}

