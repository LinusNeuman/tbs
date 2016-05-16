#include "stdafx.h"
#include "Enemy.h"
#include "../JsonDataStructs.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Init(const ActorData &aActorData, const EnemyData &aEnemyData)
{
	Actor::Init(aActorData);
	//Do stuff with enemydata
}
