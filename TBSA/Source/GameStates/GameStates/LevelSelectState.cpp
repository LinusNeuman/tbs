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
	myShouldGoBack = false;
}

LevelSelectState::~LevelSelectState()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eGoToLevel, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eGoToMainMenu, *this);
}

void LevelSelectState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eGoToLevel, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eGoToMainMenu, *this);


	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/GUI/LevelSelect/levelSelectBackground.dds", false);
	myBackgroundSprite->SetLayer(enumRenderLayer::eGameObjects);
	myLevel = 0;

	LoadGUI("LevelSelect");

	myMouseController.Init();
}

eStackReturnValue LevelSelectState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	
	myMouseController.SetMouseState(enumMouseState::eClickedOnEmptyTile);

	myGUIManager.Update(aTimeDelta);

	if (IsometricInput::GetKeyPressed(DIK_ESCAPE) == true || myShouldGoBack == true)
	{
		myShouldGoBack = false;
		return eStackReturnValue::eDeleteMainState;
	}

	if (myLevel != 0)
	{
		PlayState *newState = new PlayState();
		switch(myLevel)
		{
		case 1: mySelectedLevel = "1_Treehouse.json";
			break;
		case 2: mySelectedLevel = "2_Backyard.json";
			break;
		case 3: mySelectedLevel = "3_Lakeside.json";
			break;
		case 4: mySelectedLevel = "4_Kiosk.json";
			break;
		case 5: mySelectedLevel = "5_Playground.json";
			break;
		case 6: mySelectedLevel = "6_IcyFortress.json";
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

	myMouseController.Draw(IsometricInput::GetMouseWindowPositionNormalizedSpace());
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
	if (aMessage.myType == RecieverTypes::eGoToMainMenu)
	{
		myShouldGoBack = true;
	}
	return true;
}