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
	void NotifyPlayers() const;
private:
	CU::GrowingArray<Actor*> myPlayers;
	CU::Vector2f myMousePosition;
	Actor *mySelectedPlayer;
};

