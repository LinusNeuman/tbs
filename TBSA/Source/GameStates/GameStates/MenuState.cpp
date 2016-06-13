#include "stdafx.h"
#include "MenuState.h"
#include <CU/Vectors/Vector2.h>
#include <Rend/StaticSprite.h>
#include <StateStack/ProxyStateStack.h>
#include "PlayState.h"
#include "LevelSelectState.h"
#include "CreditsState.h"

MenuState::MenuState()
{
	myShouldAdd = false;
	myShouldSelect = false;
	myShouldGiveCred = false;
}

MenuState::~MenuState()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayGame, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eLevelSelect, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eGoToCredits, *this);
}

void MenuState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayGame, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eLevelSelect, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eGoToCredits, *this);

	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/mainMenu.dds", false, CU::Vector4f::Zero, { 0.0f, 0.0f });
	//myBackgroundSprite->Init("Sprites/mainMenu.dds", false, CU::Vector4f(0.f, 0.f, 1920.f, 1080.f), {0.5f, 0.5f});
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
	if (myShouldGiveCred == true)
	{
		CreditsState *newState = new CreditsState();
		newState->Init();
		aStateStack.AddMainState(newState);
		myShouldGiveCred = false;
	}

	return eStackReturnValue::eStay;
}

void MenuState::Draw() const
{
	myBackgroundSprite->DrawWithNormalized({0.f, 0.f});

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
	if (aMessage.myType == RecieverTypes::eGoToCredits)
	{
		myShouldGiveCred = true;
	}
	return true;
}
