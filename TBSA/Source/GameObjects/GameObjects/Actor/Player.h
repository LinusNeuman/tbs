#pragma once
#include "GameObjects/Actor/Actor.h"


struct PlayerData;
struct ActorData;
class RenderConverter;
class WrappedSprite;

class Player : public Actor 
{
public:
	Player();
	~Player();
	void Init(const ActorData &aActorData, const PlayerData &aPlayerData);
	void DecideAnimation() override;
	
	void EndTurn();
	int GetMyAP() const override;
	void CostAP(const int aCost);
	
	void ReachedTarget()override;
private:

	int myActionPointMax;
	int myCurrentAP;
};

