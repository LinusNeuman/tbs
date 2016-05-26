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

	void EndTurn();
	int GetAP() const;
	void CostAP(const int aCost);
	
private:

	int myActionPointMax;
	int myCurrentAP;
};

