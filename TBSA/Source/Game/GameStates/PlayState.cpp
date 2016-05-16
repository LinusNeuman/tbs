#include "stdafx.h"
#include "PlayState.h"
#include <CU/Vectors/Vector2.h>
#include <Rend/StaticSprite.h>
#include <ProxyStateStack.h>
#include <Rend/RenderConverter.h>
#include "../Actor/Actor.h"
#include "../PlayerController.h"
#include <TiledLoader/TiledLoader.h>
#include <TiledData/TiledData.h>
#include <Message/LevelTileMetricsMessage.h>
#include <SingletonPostMaster.h>
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
	myTiles.Init(100);

	testSprite = new StaticSprite();
	testSprite->Init("Sprites/characterSheetTurnaround.PNG", false, CU::Vector4f(0.f, 0.f, 128.f, 128.f));
	testSprite->SetLayer(enumRenderLayer::eGameObjects);
	//testSprite->SetIsIsometric(false);

	TiledLoader::Load("Data/Tiled/SecondTest.json", myTiledData);
	SingletonPostMaster::PostMessageW(LevelTileMetricsMessage(RecieverTypes::eLevelTileLayoutSettings, myTiledData.myMapSize));

	myTiles = myTiledData.myTiles;
	myPlayerFactory.LoadFromJson();
	myEnemyFactory.LoadFromJson();
	/*for (USHORT iSprite = 0; iSprite < TileCount; ++iSprite)
	{
	CU::Vector2f tempderp = CU::Vector2f(static_cast<float>(iSprite % TileRowShift), (static_cast<float>(iSprite / TileRowShift)));
	myTiles.Add(IsometricTile(tempderp));
	}*/

	//myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Init));

	myPlayerController = new PlayerController();
	myPlayer = myPlayerFactory.CreatePlayer(eActorType::ePlayerOne);
	myPlayer2 = myPlayerFactory.CreatePlayer(eActorType::ePlayerTwo);
	myPlayerController->AddPlayer(myPlayer);
	myPlayerController->AddPlayer(myPlayer2);
	myEnemy = myEnemyFactory.CreateEnemy(eActorType::eEnemyOne);
	myPlayerController->AddPlayer(myEnemy);

	picojson::value animationFile = JsonWrapper::LoadPicoValue("Data/Animations/PlayerTurnAnimation.json");
	picojson::object& animationObject = JsonWrapper::GetPicoObject(animationFile);

	myAnimation = new Animation();
	myAnimation->InitializeAnimation(animationObject);
	myPlayer->AddAnimation(myAnimation);
	myPlayer->ChangeAnimation("PlayerTurn");
}

eStackReturnValue PlayState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	(aStateStack);


	//myAnimation->UpdateAnimation();
	//myAnimation->Render();

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

	//RenderConverter::DrawLine();
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
	testSprite->Draw(CU::Vector2f(500.f, 500.f));
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
