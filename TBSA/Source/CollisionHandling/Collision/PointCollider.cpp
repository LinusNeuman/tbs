#include "stdafx.h"
#include "PointCollider.h"
#include "Collision/BoxCollider.h"
#include "Collision/CircleCollider.h"

PointCollider::PointCollider()
{
}


PointCollider::~PointCollider()
{
}

bool PointCollider::CheckCollision(const GameObjectCollider &aColliderToCheckCollisionWith) const
{
	return aColliderToCheckCollisionWith.CheckCollisionAgainstPoint(*this);
}

void PointCollider::ChangePosition(const CU::Vector2f aPosition)
{
	myPosition = aPosition;
}

bool PointCollider::CheckCollisionAgainstCircle(const CircleCollider & aColliderToCheckAgainst) const
{
	return Intersection2D::PointVsCircle(myPosition, aColliderToCheckAgainst);
}

bool PointCollider::CheckCollisionAgainstBox(const BoxCollider & aColliderToCheckAgainst) const
{
	return Intersection2D::PointInsideAABB2D(aColliderToCheckAgainst, myPosition);
}