#pragma once
#include <string>
#include "Actor/Actor.h"
#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/Vector.h>

struct PlayerData
{
	int myActionPointMax;
};

struct EnemyData
{
	
};

struct ActorData
{
	eActorType myActortype;
	std::map<std::string, Animation*> myAnimations;
};

