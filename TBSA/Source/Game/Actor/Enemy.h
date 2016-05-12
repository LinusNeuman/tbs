#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();
	void Init(const CU::Vector2f &aStartPosition, const eActorType &aActorType);
};

