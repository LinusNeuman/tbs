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
	Actor* GetSelectedPlayer();
private:
	CU::GrowingArray<Actor*> myPlayers;
	CU::Vector2f myMousePosition;
	Actor *mySelectedPlayer;
	unsigned short mySelectedPlayerIndex;
};

inline Actor* PlayerController::GetSelectedPlayer()
{
	return mySelectedPlayer;
}