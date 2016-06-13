#include "stdafx.h"
#include "PauseMenuState.h"
#include <Message/SetTargetResolutionMessage.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

PauseMenuState::PauseMenuState()
{
	myLetThroughRender = true;
	myShouldPop = false;
}


PauseMenuState::~PauseMenuState()
{
	
}

void PauseMenuState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eClosePauseMenu, *this);

	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/GUI/PauseMenu/Background.dds", false, CU::Vector4f::Zero, {0.5f, 0.5f});
	myBackgroundSprite->SetLayer(enumRenderLayer::eGUI);
	myBackgroundSprite->SetRenderPriority(100);

	LoadGUI("PauseMenu");
}

eStackReturnValue PauseMenuState::Update(const CU::Time& aTimeDelta, ProxyStateStack& aStateStack)
{
	if (myShouldPop == true || IsometricInput::GetKeyPressed(DIK_ESCAPE) == true)
	{ 
		myShouldPop = false;
		//return eStackReturnValue::ePopSubstate;
		return eStackReturnValue::eDeleteSubstate;
	}

	return eStackReturnValue::eStay;
}

void PauseMenuState::Draw() const
{
	myBackgroundSprite->Draw({ SingletonDataHolder::GetTargetResolution().x * 0.5f, SingletonDataHolder::GetTargetResolution().y * 0.5f });
}

bool PauseMenuState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eClosePauseMenu)
	{
		myShouldPop = true;
	}
	return true;
}

bool PauseMenuState::RecieveMessage(const SetTargetResolutionMessage& aMessage)
{
	myTargetResolution = aMessage.myResolution;
	return true;
}
