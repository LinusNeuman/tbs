#include "stdafx.h"
#include "LevelSelectState.h"
#include <CU/Vectors/Vector2.h>
#include <Rend/StaticSprite.h>
#include <StateStack/ProxyStateStack.h>
#include "PlayState.h"

LevelSelectState::LevelSelectState()
{
	mySelectedLevel = "";
}

LevelSelectState::~LevelSelectState()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayGame, *this);
}

void LevelSelectState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayGame, *this);

	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/mainMenu.dds", false);
	myBackgroundSprite->SetLayer(enumRenderLayer::eGameObjects);

	LoadGUI("LevelSelect");
}

eStackReturnValue LevelSelectState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	myGUIManager.Update(aTimeDelta);

	if (mySelectedLevel != "")
	{
		PlayState *newState = new PlayState();
		newState->Init(mySelectedLevel);
		aStateStack.AddMainState(newState);
	}

	return eStackReturnValue::eStay;
}

void LevelSelectState::Draw() const
{
	myBackgroundSprite->Draw(CU::Vector2f(0, 0));

	myGUIManager.Render();
}

bool LevelSelectState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::ePlayGame)
	{
		//mySelectedLevel = något;
	}
	return true;
}