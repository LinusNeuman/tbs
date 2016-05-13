#pragma once
#include <string>
#include "Actor/Actor.h"
#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/Vector.h>

struct PlayerData
{
	
};

struct EnemyData
{
	
};

struct ActorData
{
	eActorType myActortype;
	CU::Vector2f myPosition;
	std::map<std::string, Animation*> myAnimations;
};

