#pragma once

#include <CU/Intersection/Shapes2D/BaseShape2D.h>
#include <Collision/GameObjectCollider.h>

class PointCollider : public GameObjectCollider, public BaseShape2D
{
public:
	PointCollider();
	~PointCollider();

	bool virtual CheckCollision(const GameObjectCollider &aColliderToCheckCollisionWith) const override;
	virtual void ChangePosition(const CU::Vector2f aPosition) override;

	bool virtual CheckCollisionAgainstCircle(const CircleCollider & aColliderToCheckAgainst) const override;
	bool virtual CheckCollisionAgainstBox(const BoxCollider & aColliderToCheckAgainst) const override;

	CU::Vector2f GetPosition() const;

private:
	CU::Vector2f myPosition;
};

inline CU::Vector2f PointCollider::GetPosition() const
{
	return myPosition;
}