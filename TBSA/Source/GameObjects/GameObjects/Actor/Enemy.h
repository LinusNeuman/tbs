#pragma once
#include "GameObjects/Actor/Actor.h"

struct ActorData;

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();
	void Init(ActorData aActorData);
};

