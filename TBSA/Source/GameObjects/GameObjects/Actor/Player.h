#pragma once
#include "GameObjects/Actor/Actor.h"
#include "APBox.h"


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
	int GetPreviousAP() const;
	void CostAP(const int aCost);
	void SuggestCostAP(const int aSuggestCost);
	
	void ReachedTarget()override;
	void ReachedWaypoint() override;

	virtual void OnClick() override;

	void Draw() const override;
	bool RecieveMessage(const PlayerSeenMessage & aMessage) override;
	bool RecieveMessage(const EnemyObjectMessage & aMessage) override;

	void SetTargetEnemy(const unsigned short aIndex, const TilePositionf & aEnemyPosition);
	void SetNoTarget();
	unsigned short GetEnemyTarget() const;
	virtual void AlmostReachTarget() override;
	virtual void NextToObjective() override;

	void SetIndex(const unsigned short aIndex);
	unsigned short GetIndex() const;

	void __forceinline SetSelected(bool aIsSelected)
	{
		myIsSelected = aIsSelected;
	};

	virtual void AfterTurn() override;
	void PreTurn();
	int GetPeekCost() const;
	int GetAttackCost() const;

	void Update(const CU::Time &aDeltaTime) override;


	virtual void ResetObjectiveState() override;

private:

	unsigned short myPlayerIndex;
	unsigned short myEnemyTargetIndex;
	StaticSprite* myDetectedSprite;
	int myActionPointMax;
	int myAttackCost;
	int myPeekCost;
	int myCurrentAP;
	int myPreviousAP;

	bool myIsSelected;
	bool myIsInFight;

	APBox myAPBox;
};

inline void Player::SetTargetEnemy(const unsigned short aIndex, const TilePositionf & aEnemyPosition)
{
	myEnemyTargetIndex = aIndex;
	SetObjective(aEnemyPosition);
}

inline unsigned short Player::GetEnemyTarget() const
{
	return myEnemyTargetIndex;
}

inline void Player::SetIndex(const unsigned short aIndex)
{
	myPlayerIndex = aIndex;
}

inline unsigned short Player::GetIndex() const
{
	return myPlayerIndex;
}