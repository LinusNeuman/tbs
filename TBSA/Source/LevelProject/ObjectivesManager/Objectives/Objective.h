// Author:   Hampus Huledal
// CreationDate: 09/06/2016
#pragma once
#include <string>

enum class eLevelObjectiveType
{
	KILL,
	HOLD,
	TAKE,
	Size,
};

struct LevelObjective
{
	eLevelObjectiveType myType;
	bool myIsDone;
	std::string myTarget;
	std::string dialogName;
};
