#include "stdafx.h"
#include "LevelSelectState.h"
#include <CU/Vectors/Vector2.h>
#include <Rend/StaticSprite.h>
#include <StateStack/ProxyStateStack.h>
#include "PlayState.h"
#include <Message\LevelChangeMassage.h>

LevelSelectState::LevelSelectState()
{
	mySelectedLevel = "";
	myLevel = 0;
}

LevelSelectState::~LevelSelectState()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eGoToLevel, *this);
}

void LevelSelectState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eGoToLevel, *this);


	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/mainMenu.dds", false);
	myBackgroundSprite->SetLayer(enumRenderLayer::eGameObjects);
	myLevel = 0;

	LoadGUI("LevelSelect");
}

eStackReturnValue LevelSelectState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	myGUIManager.Update(aTimeDelta);

	if (myLevel != 0)
	{
		PlayState *newState = new PlayState();
		switch(myLevel)
		{
		case 1: mySelectedLevel = "1_Treehouse.json";
			break;
		case 2: mySelectedLevel = "2_Backyard.json";
			break;
		case 3: mySelectedLevel = "2_Backyard.json";
			break;
		case 4: mySelectedLevel = "2_Backyard.json";
			break;
		case 5: mySelectedLevel = "2_Backyard.json";
			break;
		case 6: mySelectedLevel = "2_Backyard.json";
			break;
		default: mySelectedLevel = "1_Treehouse.json";
			break;
		}
		newState->Init(mySelectedLevel);
		aStateStack.AddMainState(newState);
		myLevel = 0;
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
	if (aMessage.myType == RecieverTypes::eGoToLevel)
	{
		const LevelChangeMassage* massage = dynamic_cast<const LevelChangeMassage*>(&aMessage);
		if (massage == nullptr)
		{
			return false;
		}
		myLevel = massage->myLevel;
	}
	return true;
}