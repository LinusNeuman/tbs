#include "stdafx.h"
#include "PlayState.h"

#include <Level/GameLevel.h>
#include <Message/StartUpLevelMessage.h>
#include <Message/GetStartLevelMessage.h>
#include <LevelFactory\LevelFactory.h>
#include <Message/GoalReachedMessage.h>
#include "PauseMenuState.h"

#include <StateStack/StateStack.h>
#include <StateStack/ProxyStateStack.h>
#include "GameOverState.h"
#include "LoadState.h"
#include "PostLevelState.h"
#include "Message\DialogTextMessage.h"
#include "Message\ClearLogMessage.h"
#include "Message\ScrollLogDownMessage.h"
#include "Message\ScrollLogUpMessage.h"
#include <../DialogLoader/DialogManager.h>
#include <Message/TextMessage.h>

PlayState::PlayState()
{
	//myStartPath = "Data/Tiled/";

	myEmitter.LoadEmitterSettings("snow");

	myShouldPause = false;
	myGameOver = false;
	myShowPostLevelScreen = false;

	myAmbiance = new Song();
	myAmbiance->Init("Sounds/AMB/windy.ogg", true);

	myMusic = new Song();
	myMusic->Init("Sounds/MUSIC/sneakymusic.ogg", true);
}

PlayState::~PlayState()
{
	SAFE_DELETE(myLevel);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eStartUpLevel, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayEvents, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eFlagGoalReached, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eLevelEnd, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eRestartLevel, *this);
}

void PlayState::Init(const std::string& aLevelPath)
{
	myLevelFactory = new LevelFactory();

	SingletonPostMaster::AddReciever(RecieverTypes::eStartUpLevel, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eGoalReached, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eOpenPauseMenu, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eLevelEnd, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eRestartLevel, *this);
	if (aLevelPath == "")
	{
		SendPostMessage(GetStartLevelMessage(RecieverTypes::eStartUpLevel));
	}
	else
	{
		myLevelKey = aLevelPath;
	}

	//myLevels[myLevelKey] = myLevelFactory->CreateLevel(myStartPath + myLevelKey);
	myLevel = myLevelFactory->CreateLevel(myLevelKey);
	myCurrentLevelpath = myLevelKey;
	LoadGUI("InGame");

	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);

	myEmitter.Activate({0.5f, 0.5f});

	myAmbiance->Play(0.8f);
	myMusic->Play(0.58f);
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
		//return eStackReturnValue::ePopMain;
		return eStackReturnValue::eDeleteMainState;
	}

	if (IsometricInput::GetKeyPressed(DIK_1) == true)
	{
		ChangeLevel("1_Treehouse.json");
	}
	else if (IsometricInput::GetKeyPressed(DIK_2) == true)
	{
		ChangeLevel("2_Backyard.json");
	}
	else if (IsometricInput::GetKeyPressed(DIK_3) == true)
	{
		ChangeLevel("3_Lakeside.json");
	}
	else if (IsometricInput::GetKeyPressed(DIK_4) == true)
	{
		ChangeLevel("4_Kiosk.json");
	}
	else if (IsometricInput::GetKeyPressed(DIK_5) == true)
	{
		ChangeLevel("5_Playground.json");
	}
	else if (IsometricInput::GetKeyPressed(DIK_6) == true)
	{
		ChangeLevel("6_IcyFortress.json");
	}

	if (myShouldPause == true)
	{
		PauseMenuState *newState = new PauseMenuState();
		newState->Init();
		aStateStack.AddSubState(newState);
		myShouldPause = false;
	}

	if (myGameOver == true)
	{
		GameOverState *newState = new GameOverState();
		newState->Init();
		aStateStack.AddSubState(newState);
	}

	if (myLevel->GetTiledData()->myIsLoaded == false)
	{
		aStateStack.AddMainState(new LoadState(myLevel->GetTiledData()));

		if (myShowPostLevelScreen == true)
		{
			myShowPostLevelScreen = false;
			aStateStack.AddSubState(new PostLevelState(100000, 23, 4));
		}
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
	if (aMessage.myType == RecieverTypes::eRestartLevel)
	{
		ChangeLevel(myCurrentLevelpath);
	}
	return true;
}

bool PlayState::RecieveMessage(const TextMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eLevelEnd)
	{
		ChangeLevel(aMessage.myText);
		myShowPostLevelScreen = true;
	}
	return true;
}

bool PlayState::RecieveMessage(const GoalReachedMessage& aMessage)
{
	ChangeLevel(aMessage.aLevelPathNameToChangeTo);
	myShowPostLevelScreen = true;
	return true;
}

bool PlayState::RecieveMessage(const PlayerDiedMessage& aMessage)
{
	if (myGameOver == true)
	{
		ChangeLevel(myCurrentLevelpath);
		myGameOver = false;

	}
	else
	{
		myGameOver = true;
	}
	return true;
}


void PlayState::ChangeLevel(const std::string& aFilePath)
{
	if (myLevel != nullptr)
	{
		delete(myLevel);
	}
	myLevel = myLevelFactory->CreateLevel( aFilePath);
	myCurrentLevelpath = aFilePath;
}
