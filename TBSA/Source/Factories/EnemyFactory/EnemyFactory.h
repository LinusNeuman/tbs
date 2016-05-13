#pragma once
#include <CU/DLDebug/DL_Debug.h>
#include "../Game/Actor/Enemy.h"
#include <CU/Memory Pool/MemoryPool.h>
#include <CU/Vectors/vector2.h>
#include "../Game/JsonDataStructs.h"
#include <Pico/picojson.h>

class EnemyFactory
{
public:
	EnemyFactory();
	~EnemyFactory();
	void LoadFromJson();
	void UpdateDataStruct(const std::string& aStringPath, ActorData &aActorData);
	void AddEnemyAnimation(ActorData &aActorData, picojson::object& aObject);
	Enemy* CreateEnemy(eActorType aActorType);
	void ReturnEnemy(Enemy* aPlayer);
private:
	CommonUtilities::MemoryPool<Enemy, 5> myEnemyPool;
	ActorData myEnemyOneData;
	ActorData myEnemyTwoData;
};

