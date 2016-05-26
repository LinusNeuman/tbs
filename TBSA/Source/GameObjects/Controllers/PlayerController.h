#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/Timer/Time.h>
#include <CU/Vectors/vector2.h>

class PlayState;
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
	void ConstantUpdate(const CommonUtilities::Time& aTime);

	void SetMyPlayState(PlayState & aPlayState);
private:
	PlayState* myPlayState;

	CommonUtilities::GrowingArray<Actor*> myPlayers;
	CommonUtilities::Vector2f myMousePosition;
	Actor *mySelectedPlayer;
	unsigned short mySelectedPlayerIndex;
};

inline Actor* PlayerController::GetSelectedPlayer()
{
	return mySelectedPlayer;
}
