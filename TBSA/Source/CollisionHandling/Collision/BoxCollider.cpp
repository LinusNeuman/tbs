#include "stdafx.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include <Rend/RenderConverter.h>

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(const CU::Vector2f aCenterPosition, const CU::Vector2f aExtents):
Intersection2D::AABB2D(aCenterPosition, aExtents)
{

}

BoxCollider::~BoxCollider()
{
}

bool BoxCollider::CheckCollision(const GameObjectCollider &aColliderToCheckCollisionWith) const
{
	return aColliderToCheckCollisionWith.CheckCollisionAgainstBox(*this);
}

void BoxCollider::DrawCollider(const CU::Vector4f & aRenderColor /*= Vector4f::One*/) const
{
	CU::Vector2f aLinePos1 = myMinPos;
	CU::Vector2f aLinePos2 = myMinPos;

	aLinePos2.x = myMaxPos.x;

	RenderConverter::DrawIsometricLine(aLinePos1, aLinePos2);

	aLinePos1 = myMaxPos;

	RenderConverter::DrawIsometricLine(aLinePos1, aLinePos2);

	aLinePos2 = myMaxPos;
	aLinePos2.y = myMinPos.y;

	RenderConverter::DrawIsometricLine(aLinePos1, aLinePos2);

	aLinePos1 = myMinPos;

	RenderConverter::DrawIsometricLine(aLinePos1, aLinePos2);
}

bool BoxCollider::CheckCollisionAgainstCircle(const CircleCollider & aColliderToCheckAgainst) const
{
	return Intersection2D::AABBvsCircle(*this, aColliderToCheckAgainst);
}

bool BoxCollider::CheckCollisionAgainstBox(const BoxCollider & aColliderToCheckAgainst) const
{
	return Intersection2D::AABBVsAABB2D(aColliderToCheckAgainst, *this);
}
