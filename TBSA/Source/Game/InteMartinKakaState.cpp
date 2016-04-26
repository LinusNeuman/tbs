#include "stdafx.h"
#include "InteMartinKakaState.h"
#include "Renderer.h"
#include "WrappedSprite.h"
#include <ProxyStateStack.h>
#include "GameWorld.h"

InteMartinKakaState::InteMartinKakaState()
{
}


InteMartinKakaState::~InteMartinKakaState()
{
}

void InteMartinKakaState::Init()
{
	myLetThroughRender = true;

	myRenderer = new Renderer();
	myRenderer->Init("Sprites/inteKaka.png");
	myRenderer->SetWindowSize(CU::Vector2ui(1280, 720));

	myTestSprite = new WrappedSprite();

	myTestSprite->Init();
	myTestSprite->SetPosition(CU::Vector2f(300.f, 300.f));
	myRenderer->AddNodeToDraw(*myTestSprite);
}

eStackReturnValue InteMartinKakaState::Update(const CU::Time & aDeltaTime, ProxyStateStack & aStateStack)
{
	myTestSprite->SetPosition(myTestSprite->GetPosition() + CU::Vector2f(5.f, 0.f) * aDeltaTime.GetSeconds());
	if (myTestSprite->GetPosition().x >= 700.f)
	{
		myTestSprite->SetPosition(CU::Vector2f(300.f, 300.f));
	}

	if (GetInput::GetKeyPressed(DIK_A) == true)
	{
		CGameWorld * tempState = new CGameWorld();
		tempState->Init();
		aStateStack.AddMainState(tempState);
	}

	if (GetInput::GetKeyPressed(DIK_END) == true)
	{
		return eStackReturnValue::ePopSubState;
	}
	if (GetInput::GetKeyPressed(DIK_HOME) == true)
	{
		return eStackReturnValue::ePopCurrentSubStates;
	}
	if (GetInput::GetKeyPressed(DIK_DELETE) == true)
	{
		return eStackReturnValue::ePopMain;
	}

	return eStackReturnValue::eStay;
}

void InteMartinKakaState::Draw()
{
	myRenderer->UpdateSprite(*myTestSprite);
	myRenderer->Draw();	
}
