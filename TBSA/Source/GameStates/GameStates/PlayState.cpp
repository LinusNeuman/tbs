#include "stdafx.h"
#include "PlayState.h"

#include <Level/GameLevel.h>
#include <Message/StartUpLevelMessage.h>
#include <Message/GetStartLevelMessage.h>
#include <LevelFactory\LevelFactory.h>
#include <Message/GoalReachedMessage.h>
#include "PauseMenuState.h"

#include <StateStack/StateStack.h>

PlayState::PlayState()
{
	myLevel = new GameLevel();
	myStartPath = "Data/Tiled/";

	myEmitter.LoadEmitterSettings("snow");

	myShouldPause = false;
}

PlayState::~PlayState()
{
	SAFE_DELETE(myLevel);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eStartUpLevel, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayEvents, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eFlagGoalReached, *this);
}

void PlayState::Init(const std::string& aLevelPath)
{
	myLevelFactory = new LevelFactory();

	SingletonPostMaster::AddReciever(RecieverTypes::eStartUpLevel, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eGoalReached, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eOpenPauseMenu, *this);

	if (aLevelPath == "")
	{
		SendPostMessage(GetStartLevelMessage(RecieverTypes::eStartUpLevel));
	}
	else
	{
		myLevelKey = aLevelPath;
	}

	//myLevels[myLevelKey] = myLevelFactory->CreateLevel(myStartPath + myLevelKey);
	myLevel = myLevelFactory->CreateLevel(myStartPath + myLevelKey);
	myCurrentLevelpath = myLevelKey;
	LoadGUI("InGame");

	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);

	myEmitter.Activate({0.5f, 0.5f});
}

eStackReturnValue PlayState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	//(aStateStack);

	myGUIManager.Update(aTimeDelta);

	static int index = 0;
	
	//myLevels[myLevelKey]->Update(aTimeDelta);
	myLevel->Update(aTimeDelta);
	myEmitter.Update(aTimeDelta);

	if (IsometricInput::GetKeyPressed(DIK_ESCAPE) == true || myShouldExit == true)
	{
		myShouldExit = false;
		return eStackReturnValue::ePopMain;
	}

	if (IsometricInput::GetKeyPressed(DIK_1) == true)
	{
		ChangeLevel("1_Treehouse.json");
	}
	else if (IsometricInput::GetKeyPressed(DIK_2) == true)
	{
		ChangeLevel("2_Backyard.json");
	}
	else if (IsometricInput::GetKeyPressed(DIK_0) == true)
	{
		ChangeLevel("SecondTest.json");
	}

	if (myShouldPause == true)
	{
		PauseMenuState *newState = new PauseMenuState();
		newState->Init();
		aStateStack.AddMainState(newState);
		myShouldPause = false;
	}

	return eStackReturnValue::eStay;
}

void PlayState::Draw() const
{
	myLevel->Draw();
	myEmitter.Render();
	myGUIManager.Render();
}

bool PlayState::RecieveMessage(const StartUpLevelMessage& aMessage)
{
	myLevelKey = aMessage.myPath;
	return true;
}

bool PlayState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eOpenPauseMenu)
	{
		myShouldPause = true;
	}
	return true;
}

bool PlayState::RecieveMessage(const GoalReachedMessage& aMessage)
{
	ChangeLevel(aMessage.aLevelPathNameToChangeTo);
return true;
}

bool PlayState::RecieveMessage(const PlayerDiedMessage& aMessage)
{
	ChangeLevel(myCurrentLevelpath);
	return true;
}


void PlayState::ChangeLevel(const std::string& aFilePath)
{
	if (myLevel != nullptr)
	{
		delete(myLevel);
	}
	myLevel = myLevelFactory->CreateLevel(myStartPath + aFilePath);
	myCurrentLevelpath = aFilePath;
}
