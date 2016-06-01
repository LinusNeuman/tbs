#pragma once
#include "GameObjects/Actor/Actor.h"



struct PlayerData;
struct ActorData;

class RenderConverter;
class WrappedSprite;
class Enemy;

class Player : public Actor
{
public:
	Player();
	~Player();
	void Init(const ActorData &aActorData, const PlayerData &aPlayerData);
	void DecideAnimation() override;
	void OnMove(CU::Vector2ui aTargetPosition) override;
	void FreshTurn();
	int GetMyAP() const override;
	void CostAP(const int aCost);
	
	void ReachedTarget()override;


	virtual void OnClick() override;

	void RecieveMessage(const PlayerSeenMessage & aMessage) override;

	void SetTargetEnemy(const unsigned short aIndex);
	void SetNoTarget();
	unsigned short GetEnemyTarget();


	virtual void AlmostReachTarget() override;

private:

	unsigned short myEnemyTargetIndex;

	int myActionPointMax;
	int myCurrentAP;

	bool myIsSeen;
};

inline void Player::SetTargetEnemy(const unsigned short aIndex)
{
	myEnemyTargetIndex = aIndex;
}

inline unsigned short Player::GetEnemyTarget()
{
	return myEnemyTargetIndex;
}

