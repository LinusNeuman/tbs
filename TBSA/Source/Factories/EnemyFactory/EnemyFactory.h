#pragma once
#include <CU/DLDebug/DL_Debug.h>
#include "../Game/Actor/Enemy.h"
#include <CU/Memory Pool/MemoryPool.h>
#include <CU/Vectors/vector2.h>

struct EnemyData
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
	void UpdateDataStruct(const std::string& aStringPath, EnemyData &aEnemyData);
	Enemy* CreateEnemy(eActorType aActorType);
	void ReturnEnemy(Enemy* aPlayer);
private:
	CommonUtilities::MemoryPool<Enemy, 5> myEnemyPool;
	EnemyData myEnemyOneData;
	EnemyData myEnemyTwoData;
};

