#include "stdafx.h"
#include "GameObjectCollider.h"




GameObjectCollider::GameObjectCollider()
{
}


GameObjectCollider::~GameObjectCollider()
{
}

bool GameObjectCollider::CheckCollision(const GameObjectCollider & aCircleToTestCollisionWith) const
{
	return false;
}

void GameObjectCollider::DrawCollider(const CU::Vector4f & aRenderColor) const
{
	
}

bool GameObjectCollider::CheckCollisionAgainstCircle(const CircleCollider & aColliderToCheckAgainst) const
{
	return false;
}

bool GameObjectCollider::CheckCollisionAgainstBox(const BoxCollider & aColliderToCheckAgainst) const
{
	return false;
}
