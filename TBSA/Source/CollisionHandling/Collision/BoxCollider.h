#pragma once

#include "Collision/GameObjectCollider.h"
#include <CU/Intersection/Shapes2D/AABB2D.h>

class BoxCollider : public GameObjectCollider, public Intersection2D::AABB2D
{
public:
	BoxCollider();
	BoxCollider(const CU::Vector2f aCenterPosition, const CU::Vector2f aExtents);
	~BoxCollider();

	bool virtual CheckCollision(const GameObjectCollider &aColliderToCheckCollisionWith) const override;

	void virtual DrawCollider(const CU::Vector4f & aRenderColor = CU::Vector4f::One) const;

	bool virtual CheckCollisionAgainstCircle(const CircleCollider & aColliderToCheckAgainst) const;
	bool virtual CheckCollisionAgainstBox(const BoxCollider & aColliderToCheckAgainst) const;
};