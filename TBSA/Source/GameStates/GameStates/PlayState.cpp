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
#include <Shader/Shaders.h>

#include <TiledData/TiledData.h>
#include <Message/LevelTileMetricsMessage.h>
#include <PostMaster/SingletonPostMaster.h>
#include "../../PathFinding/NavGraph/NavHandle.h"
#include "../PathFinding/NavGraph/Vertex/NavVertex.h"
#include "../PathFinding/NavGraph/Edge/NavEdge.h"

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

	
	TiledData someData;

	TiledLoader::Load("Data/Tiled/SecondTest.json", someData);
	SingletonPostMaster::PostMessage(LevelTileMetricsMessage(RecieverTypes::eLevelTileLayoutSettings, someData.myMapSize));

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
	customShader->SetShaderdataFloat4(DX2D::Vector4f(1, 0, 1, 1), DX2D::EShaderDataID_1); // Add some data to it
	customShader->SetTextureAtRegister(DX2D::CEngine::GetInstance()->GetTextureManager().GetTexture("Sprites/Players/Player2/characterSheetTurnaround2.png"), DX2D::EShaderTextureSlot_1); // Add a texture
	customShader->PostInit("shaders/custom_sprite_vertex_shader.fx", "shaders/custom_sprite_pixel_shader.fx", DX2D::EShaderDataBufferIndex_1);

	Shaders::GetInstance()->AddShader(customShader, "testShader");

	Shaders::GetInstance()->ApplyShader(myPlayer2->mySprite, "testShader");
}

eStackReturnValue PlayState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	(aStateStack);

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

	if (IsometricInput::GetKeyReleased(DIK_Q) == true)
	{
		bool isFalse = false;
		DL_ASSERT(isFalse, "IT Works!");
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
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Draw));
	myPlayer->Draw();
	myPlayer2->Draw();
	myEnemy->Draw();

}

void PlayState::ConstructNavGraph()
{
	for (size_t i = 0; i < myTiles.Size(); i++)
	{
		if (myTiles[i].GetTileType() != eTileType::OPEN || myTiles[i].GetTileType() != eTileType::DOOR || myTiles[i].GetTileType() != eTileType::DOOR_2)
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
