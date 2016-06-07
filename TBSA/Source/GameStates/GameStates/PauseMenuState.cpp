#include "stdafx.h"
#include "PauseMenuState.h"


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
	myBackgroundSprite->Draw({ 1920.f * 0.5f, 1080.f * 0.5f });
}

bool PauseMenuState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eClosePauseMenu)
	{
		myShouldPop = true;
	}
	return true;
}
