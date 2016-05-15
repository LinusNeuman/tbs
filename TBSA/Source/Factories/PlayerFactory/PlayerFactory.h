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
	void UpdateDataStruct(const std::string& aStringPath, ActorData &aActorData);
	void AddPlayerAnimation(ActorData &aActorData, picojson::object& aObject);
	Player* CreatePlayer(eActorType aActorType);
	void ReturnPlayer(Player* aPlayer);
private:
	CommonUtilities::MemoryPool<Player, 2> myPlayerPool;
	ActorData myPlayerOneData;
	ActorData myPlayerTwoData;
};

