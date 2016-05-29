#pragma once
#include "Collision/Colliders/GameObjectCollider.h"
#include <CU/Intersection/Shapes2D/Circle2D.h>

class CircleCollider : public GameObjectCollider, public Intersection2D::Circle2D
{
public:
	CircleCollider();
	CircleCollider(const CU::Vector2f aPosition, const float aRadius);
	~CircleCollider();

	bool virtual CheckCollision(const GameObjectCollider &aColliderToCheckCollisionWith) const override;

	bool virtual CheckCollisionAgainstCircle(const CircleCollider & aColliderToCheckAgainst) const override;
	bool virtual CheckCollisionAgainstBox(const BoxCollider & aColliderToCheckAgainst) const;

	void virtual DrawCollider(const CU::Vector4f & aRenderColor = CU::Vector4f::One) const override;
};