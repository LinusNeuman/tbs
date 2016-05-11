#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite.h>
#include <CU/Vectors/Vector2.h>
#include <Rend/Renderer.h>
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
#include <Message/TestPosition.h>

#include "../TiledLoading/TiledLoader/TiledLoader.h"

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
	myRenderer = new RenderConverter();
	myRenderer->Init(CU::Vector2ui(1920, 1080));
	myTiles.Init(100);

	testSprite = new WrappedSprite();	
	testSprite->Init("Sprites/camera3.png");
	testSprite->myLayer = 1;
	
	myTester.Init();
	TiledLoader::Load("Data/Tiled/test2.json", myTiles);
	
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

	float kLeft = 0.f;
	float kRight = 0.f;
	float kUp = 0.f;
	float kDown = 0.f;
	
	if (GetInput::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft))
	{
		myPlayerController->NotifyPlayers(aTimeDelta);
	}
	if (GetInput::GetKeyPressed(DIK_TAB) == true)
	{
		myPlayerController->SelectPlayer();
	}
	if (GetInput::GetKeyDown(DIK_H) == true)
	{
		kLeft = 1.f;
	}

	if (GetInput::GetKeyDown(DIK_K) == true)
	{
		kRight = 1.f;
	}

	if (GetInput::GetKeyDown(DIK_U) == true)
	{
		kUp = 1.f;
	}

	if (GetInput::GetKeyDown(DIK_J) == true)
	{
		kDown = 1.f;
	}

	if (GetInput::GetKeyReleased(DIK_Q) == true)
	{
		bool isFalse = false;
		DL_ASSERT(isFalse, "IT Works!");
	}

	if (GetInput::GetKeyReleased(DIK_R) == true)
	{
		TestPositionMessage testMessage(RecieverTypes::ePlayer, CU::Vector2f(6.f, 6.f));
		SingletonPostMaster::PostMessage(testMessage);
	}

	CU::Vector2f InputVector(kRight - kLeft, kDown - kUp);

	myPlayer->Update(aTimeDelta);
	myPlayer2->Update(aTimeDelta);
	myEnemy->Update(aTimeDelta);
	return eStackReturnValue::eStay;
}

void CGameWorld::Draw() const
{
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Draw));
	myRenderer->Draw();
	myPlayer->Draw();

	testSprite->Draw(CU::Vector2f(5.f, 5.f));

	myPlayer2->Draw();
	myEnemy->Draw();

	myTester.Draw();
}

void CGameWorld::SwapBuffers()
{
	myRenderer->SwapBuffers();
}
