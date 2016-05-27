#pragma once
#include <CU/DLDebug/DL_Debug.h>
#include <GameObjects/Actor/Player.h>
#include <CU/Memory Pool/MemoryPool.h>
#include <GameObjects/JsonDataStructs.h>
#include <Pico/picojson.h>

class PlayerFactory
{
public:
	PlayerFactory();
	~PlayerFactory();
	void LoadFromJson();
	void UpdateDataStruct(const std::string& aStringPath, ActorData &aActorData, PlayerData &aPlayerData);
	void AddPlayerAnimation(ActorData &aActorData, PlayerData &aPlayerData, picojson::object& aObject);
	Player* CreatePlayer(eActorType aActorType);
	void ReturnPlayer(Player* aPlayer);
private:
	CommonUtilities::MemoryPool<Player, 3> myPlayerPool;
	ActorData myActorOneData;
	ActorData myActorTwoData;
	PlayerData myPlayerOneData;
	PlayerData myPlayerTwoData;
};

