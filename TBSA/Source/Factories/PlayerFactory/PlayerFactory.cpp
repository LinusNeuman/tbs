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
	picojson::value playerOneValues = JsonWrapper::LoadPicoValue("Data/Players/Player1.json");
	picojson::object& playerOneObject = JsonWrapper::GetPicoObject(playerOneValues);
	myPlayerOneData.myActortype = static_cast<eActorType>(JsonWrapper::GetInt("actorType", playerOneObject));
	myPlayerOneData.myPosition.x = JsonWrapper::GetFloat("startPositionX", playerOneObject);
	myPlayerOneData.myPosition.y = JsonWrapper::GetFloat("startPositionY", playerOneObject);

	//Duplicated code right now, player one and player two might be holding different properties later on :)
	//Should find a better way to do this anyway
	picojson::value playerTwoValues = JsonWrapper::LoadPicoValue("Data/Players/Player2.json");
	picojson::object& playerTwoObject = JsonWrapper::GetPicoObject(playerTwoValues);
	myPlayerTwoData.myActortype = static_cast<eActorType>(JsonWrapper::GetInt("actorType", playerTwoObject));
	myPlayerTwoData.myPosition.x = JsonWrapper::GetFloat("startPositionX", playerTwoObject);
	myPlayerTwoData.myPosition.y = JsonWrapper::GetFloat("startPositionY", playerTwoObject);
}

Player* PlayerFactory::CreatePlayer(eActorType aActorType)
{
	DL_ASSERT(aActorType <= eActorType::ePlayerTwo, "Trying to Create a Player with an EnemyType");
	Player *player = myPlayerPool.GetObject();
	switch (aActorType)
	{
	case eActorType::ePlayerOne:	 
		player->Init(myPlayerOneData.myPosition, myPlayerOneData.myActortype);
		return player;
	case eActorType::ePlayerTwo:
		player->Init(myPlayerTwoData.myPosition, myPlayerTwoData.myActortype);
		return player;
	default:
		DL_ASSERT(false, "Wrong ActorType when creating player");
		return player;
	}
}

void PlayerFactory::ReturnPlayer(Player* aPlayer)
{
	*aPlayer = Player();
	myPlayerPool.RecycleObject(aPlayer);
}
