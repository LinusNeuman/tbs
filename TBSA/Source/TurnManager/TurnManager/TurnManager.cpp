#include "stdafx.h"
#include "TurnManager.h"
#include <PostMaster/SingletonPostMaster.h>
#include <Message/NavigationClearMessage.h>

TurnManager::TurnManager(): myCurrentTurn(static_cast<eTurn>(0))
{
}

TurnManager::~TurnManager()
{
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

void TurnManager::EndTurn()
{
	int turnIndex = static_cast<int>(myCurrentTurn);
	++turnIndex;

	if (turnIndex >= static_cast<int>(eTurn::Size))
	{
		turnIndex = 0;
	}

	myCurrentTurn = static_cast<eTurn>(turnIndex);
}

void TurnManager::PreparePlayer()
{
	//TODO: player preparation
	EndTurn();
}

void TurnManager::UpdatePlayer(CommonUtilities::Time aDeltaTime)
{
	myPlayerController.Update(aDeltaTime);
}

void TurnManager::PlayerEndTurn()
{
	SingletonPostMaster::PostMessage(NavigationClearMessage(RecieverTypes::eRoom));
	EndTurn();
}

void TurnManager::PrepareEnemy()
{
	//TODO: Preapre Enemy;
	EndTurn();
}

void TurnManager::UpdateEnemy(CommonUtilities::Time aDeltaTime)
{
	myEnemyController.Update(aDeltaTime);
}
