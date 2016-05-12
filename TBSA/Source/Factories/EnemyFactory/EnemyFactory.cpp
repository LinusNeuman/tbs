#include "stdafx.h"
#include "EnemyFactory.h"
#include <JsonWrapper/JsonWrapper.h>


EnemyFactory::EnemyFactory()
{
}


EnemyFactory::~EnemyFactory()
{

}

void EnemyFactory::LoadFromJson()
{
	UpdateDataStruct("Data/Enemies/Enemy1.json", myEnemyOneData);
	UpdateDataStruct("Data/Enemies/Enemy2.json", myEnemyTwoData);
}

void EnemyFactory::UpdateDataStruct(const std::string &aStringPath,  EnemyData &aEnemyData)
{
	picojson::value enemyValue = JsonWrapper::LoadPicoValue(aStringPath);
	picojson::object& enemyObject = JsonWrapper::GetPicoObject(enemyValue);
	aEnemyData.myActortype = static_cast<eActorType>(JsonWrapper::GetInt("actorType", enemyObject));
	aEnemyData.myPosition.x = JsonWrapper::GetInt("startPositionX", enemyObject);
	aEnemyData.myPosition.y = JsonWrapper::GetInt("startPositionY", enemyObject);
}

Enemy* EnemyFactory::CreateEnemy(eActorType aActorType)
{
	DL_ASSERT(aActorType >= eActorType::eEnemyOne, "Trying to Create a enemy with an PlayerType");
	Enemy *Enemy = myEnemyPool.GetObject();
	switch (aActorType)
	{
	case eActorType::eEnemyOne:
		Enemy->Init(myEnemyOneData.myPosition, myEnemyOneData.myActortype);
		return Enemy;
	case eActorType::eEnemyTwo:
		Enemy->Init(myEnemyTwoData.myPosition, myEnemyTwoData.myActortype);
		return Enemy;
	default:
		break;
	}
}

void EnemyFactory::ReturnEnemy(Enemy* aEnemy)
{
	*aEnemy = Enemy();
	myEnemyPool.RecycleObject(aEnemy);
}
