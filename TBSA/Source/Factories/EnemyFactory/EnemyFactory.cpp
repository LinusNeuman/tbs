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
	picojson::value enemyOneValues = JsonWrapper::LoadPicoValue("Data/Enemies/Enemy1.json");
	picojson::object& enemyOneObject = JsonWrapper::GetPicoObject(enemyOneValues);
	myEnemyOneData.myActortype = static_cast<eActorType>(JsonWrapper::GetInt("actorType", enemyOneObject));
	myEnemyOneData.myPosition.x = JsonWrapper::GetInt("startPositionX", enemyOneObject);
	myEnemyOneData.myPosition.y = JsonWrapper::GetInt("startPositionY", enemyOneObject);

	//Duplicated code right now, enemy one and enemy two might be holding different properties later on :)
	//Should find a better way to do this
	picojson::value enemyTwoValues = JsonWrapper::LoadPicoValue("Data/Enemies/Enemy2.json");
	picojson::object& enemyTwoObject = JsonWrapper::GetPicoObject(enemyTwoValues);
	myEnemyTwoData.myActortype = static_cast<eActorType>(JsonWrapper::GetInt("actorType", enemyTwoObject));
	myEnemyTwoData.myPosition.x = JsonWrapper::GetInt("startPositionX", enemyTwoObject);
	myEnemyTwoData.myPosition.y = JsonWrapper::GetInt("startPositionY", enemyTwoObject);
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
