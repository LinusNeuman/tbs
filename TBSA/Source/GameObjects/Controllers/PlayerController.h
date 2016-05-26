#pragma once

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

	int GetPlayerAP();
	void CostAP(const int anAP);
private:
	CU::GrowingArray<Actor*> myPlayers;
	CU::Vector2f myMousePosition;
	Actor *mySelectedPlayer;
	unsigned short mySelectedPlayerIndex;
};

