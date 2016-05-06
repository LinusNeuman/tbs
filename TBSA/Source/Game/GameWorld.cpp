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
#include "Player/Player.h"
#include "PlayerController.h"


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
	if (myTestSprite != nullptr)
	{
		SAFE_DELETE(myTestSprite);
	}
}


void CGameWorld::Init()
{
	myRenderer = new RenderConverter();
	myRenderer->Init(CU::Vector2ui(1920, 1080));
	myTiles.Init(100);

	
	

	myTestSprite = new WrappedSprite();

	for (USHORT iSprite = 0; iSprite < TileCount; ++iSprite)
	{
		//myTiles.Add(new WrappedSprite());
		//myTiles.GetLast()->Init();

		CU::Vector2f tempderp = CU::Vector2f(static_cast<float>(iSprite % TileRowShift), (static_cast<float>(iSprite / TileRowShift)));
		myTiles.Add(IsometricTile(tempderp));
	}

	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Init));

	myTestSprite->Init();
	myTestSprite->SetPosition(CU::Vector2f(125.f, 125.f));
	myPlayer = new Player(CU::Vector2f(1,1), 1);
	myPlayerController = new PlayerController();
	myPlayerController->AddPlayer(myPlayer);
	myPlayer2 = new Player(CU::Vector2f(4, 5), 2);
	myPlayerController->AddPlayer(myPlayer2);
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

	CU::Vector2f InputVector(kRight - kLeft, kDown - kUp);

	CU::Vector2f CurrentPosition = myTestSprite->GetPosition();

	CurrentPosition += InputVector * Speed * aTimeDelta.GetSeconds();

	myTestSprite->SetPosition(CurrentPosition);
	myPlayer->Update(aTimeDelta);
	myPlayer2->Update(aTimeDelta);
	return eStackReturnValue::eStay;
}

void CGameWorld::Draw() const
{
	//myTestTile.Draw();

	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Draw));
	myTestSprite->Draw();
	myRenderer->Draw();
	myPlayer->Draw();
	myPlayer2->Draw();
}

void CGameWorld::SwapBuffers()
{
	myRenderer->SwapBuffers();
}
