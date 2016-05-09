#pragma once
#include "Actor/Actor.h"

class Enemy : public Actor
{
public:
	Enemy(const CU::Vector2f &aStartPosition, const eActorType &aActorType);
	~Enemy();
};

