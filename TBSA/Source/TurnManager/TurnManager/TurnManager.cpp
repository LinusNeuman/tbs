﻿#include "stdafx.h"
#include "TurnManager.h"
#include <PostMaster/SingletonPostMaster.h>
#include <Message/NavigationClearMessage.h>
#include "../../GUI/GUI/Messaging/Generic/GUIMessage.h"
#include <Message/PlayerDiedMessage.h>

TurnManager::TurnManager() : myCurrentTurn(static_cast<eTurn>(0)), myPlayerDied(false)
{
	SingletonPostMaster::AddReciever(RecieverTypes::eFlagPlayerDied, *this);
	//ForceTurn(eTurn::ENEMY_END_TURN);
}

TurnManager::~TurnManager()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eFlagPlayerDied, *this);
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

void TurnManager::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eTurn)
	{
		EndTurn();
	}
}

void TurnManager::RecieveMessage(const FlagPlayerDiedMessage&)
{
	myPlayerDied = true;
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
	myPlayerController.PrePlayer();
	EndTurn();
	return true;
}

bool TurnManager::UpdatePlayer(CommonUtilities::Time aDeltaTime)
{
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
	myEnemyController.Update(aDeltaTime);
	return true;
}

bool TurnManager::EnemyEndTurn()
{
	myEnemyController.PostTurn();
	EndTurn();
	return true;
}
