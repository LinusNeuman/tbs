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
#include "Actor/Enemy.h"
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


eStackReturnValue CGameWorld::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	(aStateStack);

	float kLeft = 0.f;
	float kRight = 0.f;
	float kUp = 0.f;
	float kDown = 0.f;

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
	if (IsometricInput::GetKeyPressed(DIK_1) == true)
	{

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

void CGameWorld::Draw() const
{
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Draw));
	myPlayer->Draw();
	myPlayer2->Draw();
	testSprite->Draw(CU::Vector2f(5.f, 5.f));
	myEnemy->Draw();


}
