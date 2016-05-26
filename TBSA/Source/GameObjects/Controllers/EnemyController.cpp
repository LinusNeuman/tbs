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
}

void EnemyController::Update(CommonUtilities::Time)
{
	myEnemies[myCurrentEnemy].UpdateEnemy();
}

void EnemyController::ConstantUpdate(CommonUtilities::Time aDeltaTime)
{
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myEnemies[i].Update(aDeltaTime);
	}
}

void EnemyController::Draw()
{
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myEnemies[i].Draw();
	}
}

void EnemyController::EnemyDone()
{
	++myCurrentEnemy;
	if (myCurrentEnemy == myEnemies.Size())
	{
		SingletonPostMaster::PostMessage(EndTurnMessage(RecieverTypes::eTurn));
	}
}
