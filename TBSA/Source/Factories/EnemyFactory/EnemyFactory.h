#pragma once
#include <CU/DLDebug/DL_Debug.h>
#include <GameObjects/Actor/Enemy.h>
#include <CU/Memory Pool/MemoryPool.h>
#include <CU/Vectors/vector2.h>
#include <GameObjects/JsonDataStructs.h>
#include <Pico/picojson.h>

class EnemyFactory
{
public:
	EnemyFactory();
	~EnemyFactory();
	void LoadFromJson();
	void UpdateDataStruct(const std::string& aStringPath, ActorData &aActorData, EnemyData &aEnemyData);
	void AddEnemyAnimation(ActorData &aActorData, EnemyData &aEnemyData, picojson::object& aObject);
	Enemy* CreateEnemy(eActorType aActorType);
	void ReturnEnemy(Enemy* aPlayer);
private:
	CommonUtilities::MemoryPool<Enemy, 15> myEnemyPool;
	ActorData myActorOneData;
	ActorData myActorTwoData;
	ActorData myActorThreeData;
	ActorData myActorFourData;
	ActorData myActorFiveData;

	EnemyData myEnemyOneData;
	EnemyData myEnemyTwoData;
	EnemyData myEnemyThreeData;
	EnemyData myEnemyFourData;
	EnemyData myEnemyFiveData;
};

