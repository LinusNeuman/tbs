#include "stdafx.h"
#include "EnemyController.h"
#include "PostMaster/SingletonPostMaster.h"
#include <Message/EndTurnMessage.h>

EnemyController::EnemyController()
{
	myEnemies.Init(1);
	myCurrentEnemy = 0;
}

EnemyController::~EnemyController()
{
}

void EnemyController::PreTurn()
{
	myCurrentEnemy = 0;
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myEnemies[i]->Reset();
	}
}

void EnemyController::Update(CommonUtilities::Time)
{
	if (myEnemies.Size() > 0)
	{
		myEnemies[myCurrentEnemy]->UpdateEnemy();
	}
	else
	{
		SendPostMessage(EndTurnMessage(RecieverTypes::eTurn));
	}
}

void EnemyController::Draw()
{
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myEnemies[i]->Draw();
	}
}

void EnemyController::EnemyDone()
{
	++myCurrentEnemy;
	if (myCurrentEnemy == myEnemies.Size())
	{
		SendPostMessage(EndTurnMessage(RecieverTypes::eTurn));
	}
}

void EnemyController::AddEnemy(Enemy* aEnemy)
{
	aEnemy->myController = this;
	myEnemies.Add(aEnemy);
}

