#include "stdafx.h"
#include "CreditsState.h"
#include <Rend\RenderConverter.h>

CreditsState::CreditsState()
{
	myShouldGoBack = false;
}

CreditsState::~CreditsState()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eGoToMainMenu, *this);
}

void CreditsState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eGoToMainMenu, *this);

	myPosition.x = 0.25f;
	myPosition.y = 1.f;
	myCreditSprite = new StaticSprite();
	myCreditSprite->Init("Sprites/credits.dds", false, CU::Vector4f::Zero, { 0.0f, 0.0f });
	myCreditSprite->SetLayer(enumRenderLayer::eGameObjects);

	//RenderConverter::

	LoadGUI("Credits");
}

eStackReturnValue CreditsState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	myGUIManager.Update(aTimeDelta);
	if (myPosition.y <= -2.0f || IsometricInput::GetKeyPressed(DIK_ESCAPE) == true || myShouldGoBack == true)
	{
		myShouldGoBack = false;
		return eStackReturnValue::eDeleteMainState;
	}
	myPosition.y -= 0.1 * aTimeDelta.GetSeconds();
	return eStackReturnValue::eStay;
}

void CreditsState::Draw() const
{
	myCreditSprite->DrawWithNormalized({ myPosition.x, myPosition.y });

	myGUIManager.Render();
}

bool CreditsState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eGoToMainMenu)
	{
		myShouldGoBack = true;
	}
	return true;
}