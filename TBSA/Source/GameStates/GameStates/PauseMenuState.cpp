#include "stdafx.h"
#include "PauseMenuState.h"


PauseMenuState::PauseMenuState()
{
	
}


PauseMenuState::~PauseMenuState()
{
	
}

void PauseMenuState::Init()
{
	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/GUI/PauseMenu/Background.dds", false);
	myBackgroundSprite->SetLayer(enumRenderLayer::eGUI);

	LoadGUI("PauseMenu");
}

eStackReturnValue PauseMenuState::Update(const CU::Time& aTimeDelta, ProxyStateStack& aStateStack)
{
	return eStackReturnValue::eStay;
}

void PauseMenuState::Draw() const
{
}

bool PauseMenuState::RecieveMessage(const GUIMessage& aMessage)
{
	return true;
}
