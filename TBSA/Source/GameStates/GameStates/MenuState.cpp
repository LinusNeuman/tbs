#include "stdafx.h"
#include "MenuState.h"
#include <CU/Vectors/Vector2.h>
#include <Rend/StaticSprite.h>
#include <StateStack/ProxyStateStack.h>
#include "PlayState.h"
#include "LevelSelectState.h"

MenuState::MenuState()
{
	myShouldAdd = false;
	myShouldSelect = false;
}

MenuState::~MenuState()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayGame, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eLevelSelect, *this);
}

void MenuState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayGame, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eLevelSelect, *this);

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
		myShouldAdd = false;
	}
	if (myShouldSelect == true)
	{
		LevelSelectState *newState = new LevelSelectState();
		newState->Init();
		aStateStack.AddMainState(newState);
		myShouldSelect = false;
	}

	return eStackReturnValue::eStay;
}

void MenuState::Draw() const
{
	myBackgroundSprite->Draw(CU::Vector2f(0, 0));

	myGUIManager.Render();
}

bool MenuState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::ePlayGame)
	{
		myShouldAdd = true;
	}
	if (aMessage.myType == RecieverTypes::eLevelSelect)
	{
		myShouldSelect = true;
	}
	return true;
}
