#pragma once

class Player;
class RenderConverter;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();
	void AddPlayer(Player *aPlayer);
	void NotifyPlayers(const CU::Time aDeltaTime);
private:
	CU::GrowingArray<Player*> myPlayers;
	CU::Vector2f myMousePosition;
};

