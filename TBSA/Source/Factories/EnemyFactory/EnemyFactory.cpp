#include "stdafx.h"
#include "EnemyFactory.h"
#include <JsonWrapper/JsonWrapper.h>
#include <Animation/Animation.h>

EnemyFactory::EnemyFactory()
{
}


EnemyFactory::~EnemyFactory()
{

}

void EnemyFactory::LoadFromJson()
{
	UpdateDataStruct("Data/Enemies/Enemy1.json", myActorOneData, myEnemyOneData);
	UpdateDataStruct("Data/Enemies/Enemy2.json", myActorTwoData, myEnemyTwoData);
	UpdateDataStruct("Data/Enemies/Enemy3.json", myActorThreeData, myEnemyThreeData);
	UpdateDataStruct("Data/Enemies/Enemy4.json", myActorFourData, myEnemyFourData);
	UpdateDataStruct("Data/Enemies/Enemy5.json", myActorFiveData, myEnemyFiveData);
}

void EnemyFactory::UpdateDataStruct(const std::string &aStringPath, ActorData &aActorData, EnemyData &aEnemyData)
{
	picojson::value enemyValue = JsonWrapper::LoadPicoValue(aStringPath);
	picojson::object& enemyObject = JsonWrapper::GetPicoObject(enemyValue);
	aActorData.myActortype = static_cast<eActorType>(JsonWrapper::GetInt("actorType", enemyObject));
	aEnemyData.myActionPoints = JsonWrapper::GetInt("actionPoints", enemyObject);
	aEnemyData.myViewDistance = JsonWrapper::GetInt("viewDistance", enemyObject);
	AddEnemyAnimation(aActorData, aEnemyData, enemyObject);
}

void EnemyFactory::AddEnemyAnimation(ActorData &aActorData, EnemyData &aEnemyData,picojson::object& aObject)
{
	picojson::array& animationArray = JsonWrapper::GetPicoArray("animations", aObject);
	for (size_t i = 0; i < animationArray.size(); i++)
	{
		Animation *animation = new Animation();
		std::string path = JsonWrapper::GetString("path", animationArray[i].get<picojson::object>());
		picojson::value animationFile = JsonWrapper::LoadPicoValue(path);
		picojson::object& animationObject = JsonWrapper::GetPicoObject(animationFile);
		std::string name = JsonWrapper::GetString("Name", animationObject);
		animation->InitializeAnimation(animationObject);
		aActorData.myAnimations[name] = *animation;
	}
}

Enemy* EnemyFactory::CreateEnemy(eActorType aActorType)
{
	DL_ASSERT(aActorType >= eActorType::eEnemyOne, "Trying to Create a enemy with a PlayerType");
	Enemy *Enemy = myEnemyPool.GetObject();
	switch (aActorType)
	{
	case eActorType::eEnemyOne:
		Enemy->Init(myActorOneData, myEnemyOneData);
		return Enemy;
	case eActorType::eEnemyTwo:
		Enemy->Init(myActorTwoData, myEnemyTwoData);
		return Enemy;
	case eActorType::eEnemyThree:
		Enemy->Init(myActorThreeData, myEnemyThreeData);
		return Enemy;
	case eActorType::eEnemyFour:
		Enemy->Init(myActorFourData, myEnemyFourData);
		return Enemy;
	case eActorType::eEnemyFive:
		Enemy->Init(myActorFiveData, myEnemyFiveData);
		return Enemy;
	default:
		DL_ASSERT(false, "Wrong ActorType when creating enemy");
		return Enemy;

	}
}

void EnemyFactory::ReturnEnemy(Enemy* aEnemy)
{
	*aEnemy = Enemy();
	myEnemyPool.RecycleObject(aEnemy);
}
