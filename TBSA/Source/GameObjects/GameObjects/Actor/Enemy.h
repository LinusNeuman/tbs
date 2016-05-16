#pragma once
#include "GameObjects/Actor/Actor.h"

struct EnemyData;
struct ActorData;

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();
	void Init(const ActorData &aActorData, const EnemyData &aEnemyData);
};

