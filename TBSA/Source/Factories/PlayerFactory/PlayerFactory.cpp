#include "stdafx.h"
#include "PlayerFactory.h"
#include <JsonWrapper/JsonWrapper.h>
#include <Animation/Animation.h>


PlayerFactory::PlayerFactory()
{
}


PlayerFactory::~PlayerFactory()
{
}

void PlayerFactory::LoadFromJson()
{
	UpdateDataStruct("Data/Players/Player1.json", myActorOneData, myPlayerOneData);
	UpdateDataStruct("Data/Players/Player2.json", myActorTwoData, myPlayerTwoData);
}

void PlayerFactory::UpdateDataStruct(const std::string& aStringPath, ActorData& aActorData, PlayerData &aPlayerData)
{
	picojson::value values = JsonWrapper::LoadPicoValue(aStringPath);
	picojson::object& object = JsonWrapper::GetPicoObject(values);
	aPlayerData.myActionPointMax = JsonWrapper::GetInt("maxActionPoints", object);
	aActorData.myActortype = static_cast<eActorType>(JsonWrapper::GetInt("actorType", object));
	/*aActorData.myPosition.x = JsonWrapper::GetFloat("startPositionX", object);
	aActorData.myPosition.y = JsonWrapper::GetFloat("startPositionY", object);*/
	aPlayerData.myAttackCost = JsonWrapper::GetInt("attackCost", object);
	aPlayerData.myPeekCost = JsonWrapper::GetInt("peekCost", object);
	AddPlayerAnimation(aActorData, aPlayerData, object);
}

void PlayerFactory::AddPlayerAnimation(ActorData &aActorData, PlayerData &aPlayerData, picojson::object& aObject)
{
	picojson::array& animationArray = JsonWrapper::GetPicoArray("animations", aObject);
	for (size_t i = 0; i < animationArray.size(); i++)
	{
		Animation *animation = new Animation();
		std::string path = JsonWrapper::GetString("path", animationArray[i].get<picojson::object>());
		picojson::value animationFile = JsonWrapper::LoadPicoValue(path);
		picojson::object& animationObject = JsonWrapper::GetPicoObject(animationFile);
		std::string name = JsonWrapper::GetString("Name", animationObject);
		animation->InitializeAnimation(animationObject);
		aActorData.myAnimations[name] = *animation;
	}
}

Player* PlayerFactory::CreatePlayer(eActorType aActorType)
{
	DL_ASSERT(aActorType <= eActorType::ePlayerTwo, "Trying to Create a Player with an EnemyType");
	Player *player = myPlayerPool.GetObject();
	switch (aActorType)
	{
	case eActorType::ePlayerOne:	 
		player->Init(myActorOneData, myPlayerOneData);
		return player;
	case eActorType::ePlayerTwo:
		player->Init(myActorTwoData, myPlayerTwoData);
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
