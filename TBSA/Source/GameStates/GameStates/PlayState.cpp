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
#include "VictoryState.h"
#include "Message/DeadEnemyDataMessage.h"
#include <Message/CheckpointMessage.h>

PlayState::PlayState()
{
	//myStartPath = "Data/Tiled/";

	myEmitter.LoadEmitterSettings("snow");

	scoreScreenDone = true;
	myShouldPause = false;
	myGameOver = false;
	myShowPostLevelScreen = false;

	myAmbiance = new SoundEffect();
	myAmbiance->Init("Sounds/AMB/windy.ogg", true);

	myMusic = new Song();
	myMusic->Init("Sounds/MUSIC/sneakymusic.ogg", true);
}

PlayState::~PlayState()
{
	SAFE_DELETE(myLevel);

	myAmbiance->Stop();
	myMusic->Stop();

	SAFE_DELETE(myAmbiance);
	SAFE_DELETE(myMusic);

	SingletonPostMaster::RemoveReciever(RecieverTypes::eStartUpLevel, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayEvents, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eFlagGoalReached, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eOpenPauseMenu, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eLevelEnd, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eRestartLevel, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eLevelEndScoreMessage, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eGameOverScore, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eTriggeredCheckpoint, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eDeadEnemyData, *this);
}

void PlayState::Init(const std::string& aLevelPath)
{
	myLevelFactory = new LevelFactory();

	SingletonPostMaster::AddReciever(RecieverTypes::eStartUpLevel, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eGoalReached, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eOpenPauseMenu, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eLevelEnd, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eRestartLevel, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eLevelEndScoreMessage, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eGameOverScore, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eTriggeredCheckpoint, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eDeadEnemyData, *this);

	if (aLevelPath == "")
	{
		SendPostMessage(GetStartLevelMessage(RecieverTypes::eStartUpLevel));
	}
	else
	{
		myLevelKey = aLevelPath;
	}
	myDeadEnemies.Init(10);
	//myLevels[myLevelKey] = myLevelFactory->CreateLevel(myStartPath + myLevelKey);
	myLevel = myLevelFactory->CreateLevel(myLevelKey, myCheckpointData);
	myCurrentLevelpath = myLevelKey;
	LoadGUI("InGame");

	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);

	myEmitter.Activate({0.5f, 0.5f});

	if (myAmbiance->GetIsPlaying() == false)
	{
		myAmbiance->Play(1.0f);
	}
	
	if (myMusic->GetIsPlaying() == false)
	{
		myMusic->Play(0.58f);
	}
	myHasTriggeredCheckpoint = false;
}

eStackReturnValue PlayState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	//(aStateStack);

	if (scoreScreenDone == true)
	{
		aStateStack.AddMainState(new LoadState(myLevel->GetTiledData()));
		scoreScreenDone = false;
	}

	myGUIManager.Update(aTimeDelta);

	static int index = 0;

	//myLevels[myLevelKey]->Update(aTimeDelta);
	myLevel->Update(aTimeDelta);
	myEmitter.Update(aTimeDelta);

	/*if (IsometricInput::GetKeyPressed(DIK_1) == true)
	{
		ChangeLevel("_end_");
	}*/

	if (myShouldExit == true)
	{
		myAmbiance->Stop();
		myMusic->Stop();
		myShouldExit = false;
		//return eStackReturnValue::ePopMain;
		return eStackReturnValue::eDeleteMainState;
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
		GameOverState *newState = new GameOverState(myScoreCounter.GetScore(enumScoreTypes::eCandy), myScoreCounter.GetScore(enumScoreTypes::eTurnCount), myScoreCounter.GetScore(enumScoreTypes::eEnemiesKilled));
		newState->Init();
		aStateStack.AddSubState(newState);
	}
	
	if (myLevel->GetTiledData()->myIsLoaded == false)
	{
		if (myShowPostLevelScreen == true)
		{
			myShowPostLevelScreen = false;
			aStateStack.AddSubState(new PostLevelState(myScoreCounter.GetScore(enumScoreTypes::eCandy) , myScoreCounter.GetScore(enumScoreTypes::eTurnCount), myScoreCounter.GetScore(enumScoreTypes::eEnemiesKilled)));
		}

		scoreScreenDone = true;
	}

	if (myFinishedGame == true)
	{
		VictoryState *newState = new VictoryState();
		newState->Init();
		aStateStack.AddMainState(newState);
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
		ResetSavedData();
		ChangeLevel(aMessage.myText);
		myShowPostLevelScreen = true;
	}
	return true;
}

bool PlayState::RecieveMessage(const CheckpointMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eTriggeredCheckpoint)
	{
		myCheckpointData.myRespawnPosition = aMessage.myRespawnPosition;
		myHasTriggeredCheckpoint = true;
		myCheckpointData.mySavedDeadEnemies = myDeadEnemies;
		myCheckpointData.myObjectiveState = myLevel->GetObjectiveManagerCopy();
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

bool PlayState::RecieveMessage(const ScoreCounterMessage& aMessage)
{
	myScoreCounter = aMessage.myScoreCounter;
	return true;
}

bool PlayState::RecieveMessage(const DeadEnemyMessage & aMessage)
{
	if (aMessage.myType == RecieverTypes::eDeadEnemyData)
	{
		myDeadEnemies.Add(SavedDeadEnemy({ USHORTCAST(aMessage.myEnemyData.myTilePosition.x), USHORTCAST(aMessage.myEnemyData.myTilePosition.y) }, aMessage.myEnemyData.myEnemyIndex));
	}
	return true;
}

void PlayState::ResetSavedData()
{
	myDeadEnemies.RemoveAll();
	myCheckpointData.mySavedDeadEnemies.RemoveAll();
	myCheckpointData.myRespawnPosition = CU::Vector2ui(UINT_MAX, UINT_MAX);
	myCheckpointData.myObjectiveState = ObjectiveManager();
}

void PlayState::ChangeLevel(const std::string& aFilePath)
{
	if (aFilePath == "_end_")
	{
		myFinishedGame = true;
		return;
	}
	if (myLevel != nullptr)
	{
		delete(myLevel);
	}
	myLevel = myLevelFactory->CreateLevel(aFilePath, myCheckpointData);
	myCurrentLevelpath = aFilePath;
}
