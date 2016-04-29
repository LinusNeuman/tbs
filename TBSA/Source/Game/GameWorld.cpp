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


const float Speed = 150.f;

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
	myRenderer->Init(CU::Vector2ui(1280, 720));

	myTestSprite = new WrappedSprite(*myRenderer);
	myTestSprite->Init();
	myTestSprite->SetPosition(CU::Vector2f(250.f, 250.f));

	myTestSprite1 = new WrappedSprite(*myRenderer);
	myTestSprite1->Init();
	myTestSprite1->SetPosition(CU::Vector2f(254.f, 650.f));

	myTestSprite2 = new WrappedSprite(*myRenderer);
	myTestSprite2->Init();
	myTestSprite2->SetPosition(CU::Vector2f(150.f, 150.f));
}


eStackReturnValue CGameWorld::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	(aStateStack);

	float kLeft = 0.f;
	float kRight = 0.f;
	float kUp = 0.f;
	float kDown = 0.f;

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

	return eStackReturnValue::eStay;
}

void CGameWorld::Draw() const
{
	myTestSprite->Draw();
	myTestSprite1->Draw();
	myTestSprite2->Draw();
	myRenderer->Draw();
	/*myRenderer->AddRenderCommand(myTestSprite->GetRenderCommand());
	myRenderer->AddRenderCommand(myTestSprite1->GetRenderCommand());
	myRenderer->AddRenderCommand(myTestSprite2->GetRenderCommand());
	myRenderer->Draw();*/
}

void CGameWorld::SwapBuffers()
{
	myRenderer->SwapBuffers();
}