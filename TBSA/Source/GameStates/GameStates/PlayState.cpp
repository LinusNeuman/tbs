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
	customShader = new DX2D::CCustomShader();
	customShader->SetTextureAtRegister(DX2D::CEngine::GetInstance()->GetTextureManager().GetTexture("Sprites/Players/Player2/characterSheetTurnaround2.png"), DX2D::EShaderTextureSlot_1); // Add a texture
	customShader->SetShaderdataFloat4(DX2D::Vector4f(myPlayer->GetPosition().x, myPlayer->GetPosition().y, 1.f, 1.f), DX2D::EShaderDataID_1);
	customShader->PostInit("shaders/custom_sprite_vertex_shader.fx", "shaders/custom_sprite_pixel_shader.fx", DX2D::EShaderDataBufferIndex_1);

	Shaders::GetInstance()->AddShader(customShader, "testShader");

	Shaders::GetInstance()->ApplyShader(myPlayer2->mySprite, "testShader");

	ConstructNavGraph();
}

eStackReturnValue PlayState::Update(const CU::Time & aTimeDelta, ProxyStateStack & /*aStateStack*/)
{
	//(aStateStack);

	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Update));

	const CommonUtilities::Vector2ui mousePosition = CommonUtilities::Vector2ui(IsometricInput::GetMouseWindowPositionIsometric() + CommonUtilities::Vector2f(.5,.5));
	

	if (IsometricInput::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft))
	{
		myPlayerController->NotifyPlayers();
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

	CU::Vector2f testLine(IsometricInput::GetMouseWindowPosition());
	DRAWLINE(CU::Vector2f::Zero, testLine);
	DRAWLINE(CU::Vector2f(1920.f, 0.f), testLine);
	DRAWLINE(CU::Vector2f(1920.f, 1080.f), testLine);
	DRAWLINE(CU::Vector2f(0.f, 1080.f), testLine);

	CU::Vector2f testIsoLine(IsometricInput::GetMouseWindowPositionIsometric());
	DRAWISOMETRICLINE(CU::Vector2f::Zero, testIsoLine);
	DRAWISOMETRICLINE(CU::Vector2f(0.f, 10.f), testIsoLine);
	DRAWISOMETRICLINE(CU::Vector2f(20.f, 10.f), testIsoLine);
	DRAWISOMETRICLINE(CU::Vector2f(20.f, 0.f), testIsoLine);

	myPlayer->Update(aTimeDelta);
	myPlayer2->Update(aTimeDelta);
	myEnemy->Update(aTimeDelta);

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

IsometricTile& PlayState::GetTile(unsigned aX, unsigned aY)
{
	return myTiles[myTiledData.myMapSize.x * aY + aX];
}
