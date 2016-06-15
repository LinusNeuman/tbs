#include "stdafx.h"
#include "VictoryState.h"
#include "CreditsState.h"
#include <StateStack/ProxyStateStack.h>


VictoryState::VictoryState()
{
}

VictoryState::~VictoryState()
{
}

void VictoryState::Init()
{
	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/FinishScreen/finishScreen.dds", false, { 0.f, 0.f, 1920.f, 1080.f }, { 0.5f, 0.5f });
	myBackgroundSprite->SetLayer(enumRenderLayer::eGameObjects);
}

eStackReturnValue VictoryState::Update(const CU::Time& aTimeDelta, ProxyStateStack& aStateStack)
{
	if(IsometricInput::GetAnyMouseButtonPressed() == true || IsometricInput::GetAnyKeyPressed() == true)
	{
		CreditsState *newState = new CreditsState();
		newState->Init(true);
		aStateStack.AddMainState(newState);
	}

	return eStackReturnValue::eStay;
}

void VictoryState::Draw() const
{
	myBackgroundSprite->DrawWithNormalized(CU::Vector2f(0.5f, 0.5f));
}