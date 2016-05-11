#pragma once
#include <CU/DLDebug/DL_Debug.h>
#include "../Game/Actor/Player.h"
#include <CU/Memory Pool/MemoryPool.h>

struct PlayerData
{
	eActorType myActortype;
	CU::Vector2f myPosition;
};


class PlayerFactory
{
public:
	PlayerFactory();
	~PlayerFactory();
	void LoadFromJson();
	Player* CreatePlayer();
	void ReturnPlayer(Player* aPlayer);
private:
	CommonUtilities::MemoryPool<Player, 2> myPlayerPool;
	PlayerData myPlayerData;
};

