// Author:   Hampus Huledal
// CreationDate: 09/06/2016
#pragma once
#include <string>
#include "CU/StaticArray/StaticArray.h"

class StaticSprite;

enum class eLevelObjectiveType
{
	KILL,
	HOLD,
	TAKE,
	Size,
};

struct LevelObjective
{
	CommonUtilities::StaticArray<std::shared_ptr<StaticSprite>, 2> mySprites;
	eLevelObjectiveType myType;
	bool myIsDone;
	std::string myTarget;
	std::string dialogName;
};
