#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
//#include <tga2d/sprite/sprite.h>
#include <CU/Vectors/Vector2.h>
//#include <Rend/Renderer.h>
#include <Rend/WrappedSprite.h>
#include <CU/InputWrapper/SingletonInputWrapper.h>
#include <ProxyStateStack.h>
#include <CU/Memory Pool/MemoryPool.h>
#include <Rend/RenderConverter.h>
#include "Actor/Actor.h"
#include "Actor/Player.h"
#include "PlayerController.h"
#include "Enemy.h"
#include <TiledLoader/TiledLoader.h>
#include <SingletonPostMaster.h>
//#include <Message/TestPosition.h>

//#include "../TiledLoading/TiledLoader/TiledLoader.h"

const float Speed = 10.f;
const USHORT TileCount = 100;
const USHORT TileRowShift = 10;


template CU::MemoryPool<int, 5>;
CGameWorld::CGameWorld()
{
	// Test sound
	SoundEffect mySound;
	mySound.Init("Sounds/Horse-neigh.mp3");
	mySound.Play(0.5f);

}


CGameWorld::~CGameWorld()
{
}


void CGameWorld::Init()
{
	myTiles.Init(100);

	testSprite = new WrappedSprite();	
	testSprite->Init("Sprites/camera3.png");
	testSprite->SetLayer(enumRenderLayer::eGameObjects);

	TiledLoader::Load("Data/Tiled/SecondTest.json", myTiles);
	
	/*for (USHORT iSprite = 0; iSprite < TileCount; ++iSprite)
	{
		CU::Vector2f tempderp = CU::Vector2f(static_cast<float>(iSprite % TileRowShift), (static_cast<float>(iSprite / TileRowShift)));
		myTiles.Add(IsometricTile(tempderp));
	}*/

	//myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Init));

	
	myPlayer = new Player(CU::Vector2f(2, 1), eActorType::ePlayerOne);
	myPlayerController = new PlayerController();
	myPlayerController->AddPlayer(myPlayer);
	myPlayer2 = new Player(CU::Vector2f(4, 5), eActorType::ePlayerTwo);
	myPlayerController->AddPlayer(myPlayer2);
	myEnemy = new Enemy(CU::Vector2f(6, 6), eActorType::eEnemyOne);
}


eStackReturnValue CGameWorld::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	(aStateStack);

	if (GetInput::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft))
	{
		myPlayerController->NotifyPlayers();
	}
	if (GetInput::GetKeyPressed(DIK_TAB) == true)
	{
		myPlayerController->SelectPlayer();
	}

	if (GetInput::GetKeyReleased(DIK_Q) == true)
	{
		bool isFalse = false;
		DL_ASSERT(isFalse, "IT Works!");
	}


	myPlayer->Update(aTimeDelta);
	myPlayer2->Update(aTimeDelta);
	myEnemy->Update(aTimeDelta);
	return eStackReturnValue::eStay;
}

void CGameWorld::Draw() const
{
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Draw));
	myPlayer->Draw();

	testSprite->Draw(CU::Vector2f(5.f, 5.f));

	myPlayer2->Draw();
	myEnemy->Draw();
}
