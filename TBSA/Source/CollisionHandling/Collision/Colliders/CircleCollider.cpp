#include "stdafx.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include <CU/Matriser/matrix33.h>


CircleCollider::CircleCollider()
{

}

CircleCollider::CircleCollider(const CU::Vector2f aPosition, const float aRadius) :
Intersection2D::Circle2D(aPosition, aRadius)
{
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::CheckCollision(const GameObjectCollider &aColliderToCheckCollisionWith) const
{
	return aColliderToCheckCollisionWith.CheckCollisionAgainstCircle(*this);
}

bool CircleCollider::CheckCollisionAgainstCircle(const CircleCollider & aColliderToCheckAgainst) const
{
	return Intersection2D::CircleVSCircle(*this, aColliderToCheckAgainst);
}

bool CircleCollider::CheckCollisionAgainstBox(const BoxCollider & aColliderToCheckAgainst) const
{
	return Intersection2D::AABBvsCircle(aColliderToCheckAgainst, *this);
}

void CircleCollider::DrawCollider(const CU::Vector4f & aRenderColor /*= CU::Vector4f::One*/) const
{
	/*Vector2f startVector(myRadius, 0.f);
	Vector2f endVector = Vector2f::Zero;
	for (float angle = 60.f; angle < 360; angle += 60.f)
	{
	endVector = Vector2f(myRadius, 0.f) * Matrix33f::CreateRotateAroundZ(DEGRESS_TO_RADIANSF(angle));
	Renderer::GetInstance()->AddLineToDraw(DebugLineRenderCommand(myMainPoint + startVector, myMainPoint + endVector, aRenderColor));
	startVector = endVector;
	}
	startVector = Vector2f(myRadius, 0.f);
	Renderer::GetInstance()->AddLineToDraw(DebugLineRenderCommand(myMainPoint + startVector, myMainPoint + endVector, aRenderColor));*/
}


