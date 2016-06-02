#include "stdafx.h"
#include "TurnManager.h"
#include <PostMaster/SingletonPostMaster.h>
#include <Message/NavigationClearMessage.h>
#include "../../GUI/GUI/Messaging/Generic/GUIMessage.h"
#include <Message/PlayerDiedMessage.h>

TurnManager::TurnManager() : myCurrentTurn(static_cast<eTurn>(0)), myPlayerDied(false)
{
	SingletonPostMaster::AddReciever(RecieverTypes::eFlagPlayerDied, *this);
}

TurnManager::~TurnManager()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eFlagPlayerDied, *this);
}

void TurnManager::Update(CommonUtilities::Time aDeltaTime)
{
	switch (myCurrentTurn)
	{
	case eTurn::PRE_PLAYER_TURN: 
		PreparePlayer();
		break;
	case eTurn::PLAYER_TURN: 
		UpdatePlayer(aDeltaTime);
		break;
	case eTurn::PLAYER_END_TURN:
		PlayerEndTurn();
		break;
	case eTurn::PRE_ENEMY_TURN: 
		PrepareEnemy();
		break;
	case eTurn::ENEMY_TURN:
		UpdateEnemy(aDeltaTime);
		break;
	case eTurn::Size:
	default:
		break;
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

void TurnManager::PreparePlayer()
{
	myPlayerController.PrePlayer();
	EndTurn();
}

void TurnManager::UpdatePlayer(CommonUtilities::Time aDeltaTime)
{
	myPlayerController.Update(aDeltaTime);
}

void TurnManager::PlayerEndTurn()
{
	SendPostMessage(NavigationClearMessage(RecieverTypes::eRoom));
	myPlayerController.AfterPlayerTurn();
	EndTurn();
}

void TurnManager::PrepareEnemy()
{
	myEnemyController.PreTurn();
	EndTurn();
}

void TurnManager::UpdateEnemy(CommonUtilities::Time aDeltaTime)
{
	myEnemyController.Update(aDeltaTime);
}
