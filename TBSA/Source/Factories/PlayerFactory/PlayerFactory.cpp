#include "stdafx.h"
#include "PlayerFactory.h"
#include <JsonWrapper/JsonWrapper.h>


PlayerFactory::PlayerFactory()
{
}


PlayerFactory::~PlayerFactory()
{

}

void PlayerFactory::LoadFromJson()
{
	picojson::value playerValues = JsonWrapper::LoadPicoValue("Data/Player/Player.json");
	picojson::object& playerObject = JsonWrapper::GetPicoObject(playerValues);
	myPlayerData.myActortype = static_cast<eActorType>(JsonWrapper::GetInt("actorType", playerObject));
	myPlayerData.myPosition.x = JsonWrapper::GetInt("startPositionX", playerObject);
	myPlayerData.myPosition.y = JsonWrapper::GetInt("startPositionY", playerObject);
}

Player* PlayerFactory::CreatePlayer()
{
	Player *player = myPlayerPool.GetObject();
	player->Init(myPlayerData.myPosition, myPlayerData.myActortype);
	return player;
}

void PlayerFactory::ReturnPlayer(Player* aPlayer)
{
	myPlayerPool.RecycleObject(aPlayer);
}
