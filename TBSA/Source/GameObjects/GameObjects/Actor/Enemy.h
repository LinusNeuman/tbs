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
	void ReachedTarget()override;
	
	EnemyController* myController;
	void RecieveMessage(const PlayerSeenMessage& aMessage) override;

	virtual void DecideAnimation() override;

	void SetEnemyPath(CommonUtilities::GrowingArray<CommonUtilities::Point2ui> aEnemyPath);
	void Reset();

	virtual void OnClick() override;
	
private:
	bool myHasMoved;
	bool myHasTurned;
	bool mySomeoneSeesPlayer;
	unsigned short myCurrentPathIndex;
	CommonUtilities::GrowingArray<CommonUtilities::Point2ui> myEnemyPath;
};

