#include "stdafx.h"
#include "MenuState.h"
#include <CU/Vectors/Vector2.h>
#include <Rend/StaticSprite.h>
#include <StateStack/ProxyStateStack.h>
#include "PlayState.h"

MenuState::MenuState()
{
	myShouldAdd = false;
}

MenuState::~MenuState()
{
}

void MenuState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayGame, *this);

	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/mainMenu.dds", false);
	myBackgroundSprite->SetLayer(enumRenderLayer::eGameObjects);

	LoadGUI("MainMenu");
}

eStackReturnValue MenuState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	myGUIManager.Update(aTimeDelta);

	if (myShouldAdd == true)
	{
		PlayState *newState = new PlayState();
		newState->Init();
		aStateStack.AddMainState(newState);
	}

	return eStackReturnValue::eStay;
}

void MenuState::Draw() const
{
	myBackgroundSprite->Draw(CU::Vector2f(0, 0));

	myGUIManager.Render();
}

void MenuState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::ePlayGame)
	{
		myShouldAdd = true;
	}
}
