#include "stdafx.h"
#include "PauseMenuState.h"
#include <Message/SetTargetResolutionMessage.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

PauseMenuState::PauseMenuState()
{
	myLetThroughRender = true;
	myShouldPop = false;
	myShouldPopMain = false;
}


PauseMenuState::~PauseMenuState()
{
	SingletonPostMaster::RemoveReciever(*this);
}

void PauseMenuState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eClosePauseMenu, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eGoToMainMenu, *this);

	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/GUI/PauseMenu/Background.dds", false, CU::Vector4f::Zero, {0.5f, 0.5f});
	myBackgroundSprite->SetLayer(enumRenderLayer::eGUI);
	myBackgroundSprite->SetRenderPriority(100.f);

	LoadGUI("PauseMenu");
}

eStackReturnValue PauseMenuState::Update(const CU::Time& aTimeDelta, ProxyStateStack& aStateStack)
{
	myGUIManager.Update(aTimeDelta);

	if (myShouldPop == true || IsometricInput::GetKeyPressed(DIK_ESCAPE) == true)
	{ 
		myShouldPop = false;
		//return eStackReturnValue::ePopSubstate;
		return eStackReturnValue::eDeleteSubstate;
	}

	if (myShouldPopMain == true)
	{
		myShouldPopMain = false;

		return eStackReturnValue::eDeleteMainState;
	}

	return eStackReturnValue::eStay;
}

void PauseMenuState::Draw() const
{
	myGUIManager.Render();

	myBackgroundSprite->Draw({ SingletonDataHolder::GetTargetResolution().x * 0.5f, SingletonDataHolder::GetTargetResolution().y * 0.5f });
}

bool PauseMenuState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eClosePauseMenu)
	{
		myShouldPop = true;
	}
	if (aMessage.myType == RecieverTypes::eGoToMainMenu)
	{
		myShouldPopMain = true;
	}
	return true;
}

bool PauseMenuState::RecieveMessage(const SetTargetResolutionMessage& aMessage)
{
	myTargetResolution = aMessage.myResolution;
	return true;
}
