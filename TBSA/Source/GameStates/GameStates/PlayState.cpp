#include "stdafx.h"
#include "PlayState.h"

#include <Level/GameLevel.h>
#include <Message/StartUpLevelMessage.h>
#include <Message/GetStartLevelMessage.h>
#include <LevelFactory\LevelFactory.h>

PlayState::PlayState()
{
	myLevel = new GameLevel();
	myStartPath = "Data/Tiled/";
} 

PlayState::~PlayState()
{
	SAFE_DELETE(myLevel);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eStartUpLevel, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayEvents, *this);
}

void PlayState::Init()
{
	myLevelFactory = new LevelFactory();
	SingletonPostMaster::AddReciever(RecieverTypes::eStartUpLevel, *this);
	SendPostMessage(GetStartLevelMessage(RecieverTypes::eStartUpLevel));

	//myLevels[myLevelKey] = myLevelFactory->CreateLevel(myStartPath + myLevelKey);
	myLevel = myLevelFactory->CreateLevel(myStartPath + myLevelKey);
	myCurrentLevelpath = myLevelKey;
	LoadGUI("InGame");

	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);
}

eStackReturnValue PlayState::Update(const CU::Time & aTimeDelta, ProxyStateStack & /*aStateStack*/)
{
	//(aStateStack);

	myGUIManager.Update(aTimeDelta);

	static int index = 0;
	
	//myLevels[myLevelKey]->Update(aTimeDelta);
	myLevel->Update(aTimeDelta);

	if (IsometricInput::GetKeyPressed(DIK_ESCAPE) == true || myShouldExit == true)
	{
		myShouldExit = false;
		return eStackReturnValue::ePopMain;
	}

	if (IsometricInput::GetKeyPressed(DIK_1) == true)
	{
		ChangeLevel("SecondTest.json");
	}
	else if (IsometricInput::GetKeyPressed(DIK_2) == true)
	{
		ChangeLevel("2_Backyard.json");
	}

	return eStackReturnValue::eStay;
}

void PlayState::Draw() const
{
	myLevel->Draw();

	myGUIManager.Render();
}

void PlayState::RecieveMessage(const StartUpLevelMessage& aMessage)
{
	myLevelKey = aMessage.myPath;
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

void PlayState::RecieveMessage(const PlayerDiedMessage& aMessage)
{
	ChangeLevel(myCurrentLevelpath);
}
