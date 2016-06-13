#include "stdafx.h"
#include "CreditsState.h"

CreditsState::CreditsState()
{
}

CreditsState::~CreditsState()
{
}

void CreditsState::Init()
{
	myPosition.x = 0.f;
	myPosition.y = 1.f;
	myCreditSprite = new StaticSprite();
	myCreditSprite->Init("Sprites/credits.dds", false, CU::Vector4f::Zero, { 0.0f, 0.0f });
	myCreditSprite->SetLayer(enumRenderLayer::eGameObjects);

	LoadGUI("MainMenu");
}

eStackReturnValue CreditsState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	myGUIManager.Update(aTimeDelta);
	myPosition.y -= 0.05 * aTimeDelta.GetSeconds();
	return eStackReturnValue::eStay;
}

void CreditsState::Draw() const
{
	myCreditSprite->DrawWithNormalized({ myPosition.x, myPosition.y });

	//myGUIManager.Render();
}