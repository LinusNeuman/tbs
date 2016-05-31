#pragma once

class CircleCollider;
class BoxCollider;
class PointCollider;

class GameObjectCollider
{
public:
	
	virtual ~GameObjectCollider();

	bool virtual CheckCollision(const GameObjectCollider &aColliderToCheckCollisionWith) const = 0;

	void virtual DrawCollider(const CU::Vector4f & aRenderColor = CU::Vector4f::One) const;

	bool virtual CheckCollisionAgainstCircle(const CircleCollider & aColliderToCheckAgainst) const;
	bool virtual CheckCollisionAgainstBox(const BoxCollider & aColliderToCheckAgainst) const;
	bool virtual CheckCollisionAgainstPoint(const PointCollider & aColliderToCheckAgainst) const;

protected:
	GameObjectCollider();
};

