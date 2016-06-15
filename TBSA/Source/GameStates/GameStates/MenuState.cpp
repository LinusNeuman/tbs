#include "stdafx.h"
#include "MenuState.h"
#include <CU/Vectors/Vector2.h>
#include <Rend/StaticSprite.h>
#include <StateStack/ProxyStateStack.h>
#include "PlayState.h"
#include "PreGameState.h"
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
	myBackgroundSprite->Init("Sprites/mainMenu.dds", false, {0.f, 0.f, 1920.f, 1080.f}, { 0.5f, 0.5f });
	myBackgroundSprite->SetLayer(enumRenderLayer::eGameObjects);

	myMouseController.Init();

	LoadGUI("MainMenu");
}

eStackReturnValue MenuState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{

	myMouseController.SetMouseState(enumMouseState::eHeldOnVoid);

	myGUIManager.Update(aTimeDelta);

	if (myShouldAdd == true)
	{
		PlayState *newState = new PlayState();
		newState->Init();
		aStateStack.AddMainState(newState);
		aStateStack.AddSubState(new PreGameState);
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
	myMouseController.Draw(IsometricInput::GetMouseWindowPositionNormalizedSpace());
	
	myBackgroundSprite->DrawWithNormalized({0.5f, 0.5f});

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
