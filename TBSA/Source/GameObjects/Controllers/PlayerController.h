#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/Timer/Time.h>
#include <CU/Vectors/vector2.h>

class PlayState;
class Actor;
class RenderConverter;
class Player;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();
	void AddPlayer(Player *aPlayer);
	void SelectPlayer();
	void NotifyPlayers(CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> aPath) const;
	Player* GetSelectedPlayer();
	int GetPlayerAP();
	void CostAP(const int anAP);

	void Update(const CommonUtilities::Time& aTime);

	void SetMyPlayState(PlayState & aPlayState);
	void PrePlayer();

private:
	PlayState* myPlayState;

	CommonUtilities::GrowingArray<Player*> myPlayers;
	CommonUtilities::Vector2f myMousePosition;
	Player *mySelectedPlayer;
	unsigned short mySelectedPlayerIndex;
};

inline Player* PlayerController::GetSelectedPlayer()
{
	return mySelectedPlayer;
}
