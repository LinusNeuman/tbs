#pragma once
#include <CU/DLDebug/DL_Debug.h>
#include "../Game/Actor/Enemy.h"
#include <CU/Memory Pool/MemoryPool.h>
#include <CU/Vectors/vector2.h>

struct EnemyOneData
{
	eActorType myActortype;
	CU::Vector2f myPosition;
};

struct EnemyTwoData
{
	eActorType myActortype;
	CU::Vector2f myPosition;
};


class EnemyFactory
{
public:
	EnemyFactory();
	~EnemyFactory();
	void LoadFromJson();
	Enemy* CreateEnemy(eActorType aActorType);
	void ReturnEnemy(Enemy* aPlayer);
private:
	CommonUtilities::MemoryPool<Enemy, 5> myEnemyPool;
	EnemyOneData myEnemyOneData;
	EnemyTwoData myEnemyTwoData;
};

