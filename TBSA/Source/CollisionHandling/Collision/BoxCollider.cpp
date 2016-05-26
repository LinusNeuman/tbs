#include "stdafx.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

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
	//Vector2f aLinePos1 = myMinPos;
	//Vector2f aLinePos2 = myMinPos;

	//aLinePos2.x = myMaxPos.x;

	////Renderer::GetInstance()->AddLineToDraw(DebugLineRenderCommand(aLinePos1, aLinePos2, aRenderColor));

	//aLinePos1 = myMaxPos;

	////Renderer::GetInstance()->AddLineToDraw(DebugLineRenderCommand(aLinePos2, aLinePos1, aRenderColor));

	//aLinePos2 = myMaxPos;
	//aLinePos2.y = myMinPos.y;

	////Renderer::GetInstance()->AddLineToDraw(DebugLineRenderCommand(aLinePos1, aLinePos2, aRenderColor));

	//aLinePos1 = myMinPos;

	////Renderer::GetInstance()->AddLineToDraw(DebugLineRenderCommand(aLinePos2, aLinePos1, aRenderColor));
}

bool BoxCollider::CheckCollisionAgainstCircle(const CircleCollider & aColliderToCheckAgainst) const
{
	return Intersection2D::AABBvsCircle(*this, aColliderToCheckAgainst);
}

bool BoxCollider::CheckCollisionAgainstBox(const BoxCollider & aColliderToCheckAgainst) const
{
	return Intersection2D::AABBVsAABB2D(aColliderToCheckAgainst, *this);
}
