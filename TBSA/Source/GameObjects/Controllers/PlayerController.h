#pragma once
#include "../../GameStates/GameStates/PlayState.h"

class Actor;
class RenderConverter;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();
	void AddPlayer(Actor *aPlayer);
	void SelectPlayer();
	void NotifyPlayers(CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> aPath) const;
	Actor* GetSelectedPlayer();
	int GetPlayerAP();
	void CostAP(const int anAP);
	void Update(const CommonUtilities::Time& aTime);
private:
	PlayState* myPlayState;

	CU::GrowingArray<Actor*> myPlayers;
	CU::Vector2f myMousePosition;
	Actor *mySelectedPlayer;
	unsigned short mySelectedPlayerIndex;
};

inline Actor* PlayerController::GetSelectedPlayer()
{
	return mySelectedPlayer;
}
