#include "stdafx.h"
#include "TurnManager.h"
#include <PostMaster/SingletonPostMaster.h>
#include <Message/NavigationClearMessage.h>
#include "../../GUI/GUI/Messaging/Generic/GUIMessage.h"
#include <Message/PlayerDiedMessage.h>
#include <Message/GoalReachedMessage.h>
#include "CU\Utility\DataHolder\SingletonDataHolder.h"

TurnManager::TurnManager() : myCurrentTurn(static_cast<eTurn>(0)), myPlayerDied(false), myReachedGoal(false)
{
	SingletonPostMaster::AddReciever(RecieverTypes::eFlagPlayerDied, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eFlagGoalReached, *this);
	//ForceTurn(eEndTurn::ENEMY_END_TURN);

	myPlayerTurnImage = new StaticSprite();
	myPlayerTurnImage->Init("Sprites/trashTestFiles/Turns/GoodyTurn.dds", false);
	myPlayerTurnImage->SetLayer(enumRenderLayer::eGUI);
	myEnemyTurnImage = new StaticSprite();
	myEnemyTurnImage->Init("Sprites/trashTestFiles/Turns/BaddyTurn.dds", false);
	myEnemyTurnImage->SetLayer(enumRenderLayer::eGUI);

	myTurnImageTimer = 0.f;
}

TurnManager::~TurnManager()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eFlagPlayerDied, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eFlagGoalReached, *this);
}

bool TurnManager::Update(CommonUtilities::Time aDeltaTime)
{
	switch (myCurrentTurn)
	{
	case eTurn::PRE_PLAYER_TURN: 
		return PreparePlayer();
	case eTurn::PLAYER_TURN: 
		return UpdatePlayer(aDeltaTime);
	case eTurn::PLAYER_END_TURN:
		return PlayerEndTurn();
	case eTurn::PRE_ENEMY_TURN: 
		return PrepareEnemy();
	case eTurn::ENEMY_TURN:
		return UpdateEnemy(aDeltaTime);
	case eTurn::ENEMY_END_TURN: 
		return EnemyEndTurn();
	case eTurn::Size:
	default:
		EndTurn();
		return true;
	
	};
}

void TurnManager::ForceTurn(eTurn aTurn)
{
	myCurrentTurn = aTurn;
}

bool TurnManager::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eEndTurn)
	{
		EndTurn();
	}
	return true;
}

bool TurnManager::RecieveMessage(const FlagPlayerDiedMessage&)
{
	myPlayerDied = true;
	return true;
}

bool TurnManager::RecieveMessage(const FlagGoalReachedMessage&)
{
	myReachedGoal = true;
	return true;
}

void TurnManager::EndTurn()
{
	int turnIndex = static_cast<int>(myCurrentTurn);
	++turnIndex;

	if (turnIndex >= static_cast<int>(eTurn::Size))
	{
		turnIndex = 0;
	}

	myCurrentTurn = static_cast<eTurn>(turnIndex);
	myPlayerController.RefillAllAP();

}

bool TurnManager::PreparePlayer()
{
	myTurnImageTimer = 0.f;
	myPlayerController.PrePlayer();
	EndTurn();
	return true;
}

bool TurnManager::UpdatePlayer(CommonUtilities::Time aDeltaTime)
{
	if (myReachedGoal == true)
	{
		SendPostMessage(GoalReachedMessage(RecieverTypes::ePlayEvents, "2_Backyard.json"));
		return false;
	}

	if (myTurnImageTimer <= 4.5f)
	{
		float midPointX = (float)SingletonDataHolder::GetTargetResolution().x / 2;
		float resolutionHeight = (float)SingletonDataHolder::GetTargetResolution().x;
		myPlayerTurnImage->Draw(CU::Vector2f(midPointX - (128), resolutionHeight * 0.05f));
		myTurnImageTimer += aDeltaTime.GetSeconds();
	}

	myPlayerController.Update(aDeltaTime);
	return true;
}

bool TurnManager::PlayerEndTurn()
{
	SendPostMessage(NavigationClearMessage(RecieverTypes::eRoom));
	myPlayerController.AfterPlayerTurn();
	EndTurn();
	return true;
}

bool TurnManager::PrepareEnemy()
{
	myTurnImageTimer = 0.f;

	if (myPlayerDied == true)
	{
		SendPostMessage(PlayerDiedMessage(RecieverTypes::ePlayEvents));
		return false;
	}
	myEnemyController.PreTurn();
	EndTurn();
	return true;
}

bool TurnManager::UpdateEnemy(CommonUtilities::Time aDeltaTime)
{
	if (myTurnImageTimer <= 4.5f)
	{
		float midPointX = (float)SingletonDataHolder::GetTargetResolution().x / 2;
		float resolutionHeight = (float)SingletonDataHolder::GetTargetResolution().x;
		myEnemyTurnImage->Draw(CU::Vector2f(midPointX - (128), resolutionHeight * 0.05f));
		myTurnImageTimer += aDeltaTime.GetSeconds();
	}

	myEnemyController.Update(aDeltaTime);
	return true;
}

bool TurnManager::EnemyEndTurn()
{
	myEnemyController.PostTurn();
	EndTurn();
	return true;
}
