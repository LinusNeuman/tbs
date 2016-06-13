#pragma once
#include "GameObjects/Actor/Actor.h"


struct EnemyData;
struct ActorData;
class EnemyController;

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();
	void Init(const ActorData &aActorData, const EnemyData &aEnemyData);
	void UpdateEnemy();
	virtual void ReachedTarget()override;
	virtual void AlmostReachTarget() override;
	void SetDirection(eDirection aDirection);
	EnemyController* myController;
	bool RecieveMessage(const PlayerSeenMessage& aMessage) override;

	virtual void DecideAnimation() override;

	void SetEnemyPath(CommonUtilities::GrowingArray<CommonUtilities::Point2ui> aEnemyPath);
	void Reset();

	void SetIndex(const unsigned short aIndex);
	unsigned short GetIndex() const;
	int GetViewDistance() const;

	virtual void OnClick() override;
	
	void Fight();

	

private:
	unsigned short myIndex;

	bool myIsDeadeastFlag;
	bool myHasMoved;
	bool myHasTurned;
	bool mySomeoneSeesPlayer;
	unsigned short myCurrentPathIndex;
	int myViewDistance;
	CommonUtilities::GrowingArray<CommonUtilities::Point2ui> myEnemyPath;
};

inline void Enemy::SetIndex(const unsigned short aIndex)
{
	myIndex = aIndex;
}

inline unsigned short Enemy::GetIndex() const
{
	return myIndex;
}