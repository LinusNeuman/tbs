#include "stdafx.h"
#include "CreditsState.h"
#include "Rend\RenderConverter.h"

CreditsState::CreditsState()
{
	myShouldGoBack = false;
}

CreditsState::~CreditsState()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eGoToMainMenu, *this);
	RenderConverter::SetShouldCull(true);
}

void CreditsState::Init(bool aShouldQuit)
{
	SingletonPostMaster::AddReciever(RecieverTypes::eGoToMainMenu, *this);

	myPosition.x = 0.25f;
	myPosition.y = 1.f;
	myCreditSprite = new StaticSprite();
	myCreditSprite->Init("Sprites/credits.dds", false, CU::Vector4f::Zero, { 0.0f, 0.0f });
	myCreditSprite->SetLayer(enumRenderLayer::eGameObjects);
	myShouldQuit = aShouldQuit;

	RenderConverter::SetShouldCull(false);

	LoadGUI("Credits");
}

eStackReturnValue CreditsState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	myGUIManager.Update(aTimeDelta);
	if (myPosition.y <= -2.0f || IsometricInput::GetKeyPressed(DIK_ESCAPE) == true || myShouldGoBack == true)
	{
		if (myShouldQuit == true)
		{
			SendPostMessage(GUIMessage(RecieverTypes::eExitGame));
		}
		else
		{
			myShouldGoBack = false;
		}
		
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
