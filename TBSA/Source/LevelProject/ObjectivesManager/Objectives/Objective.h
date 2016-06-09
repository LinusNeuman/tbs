// Author:   Hampus Huledal
// CreationDate: 09/06/2016
#pragma once
#include <string>

enum class eObjectiveType
{
	KILL,
	HOLD,
	TAKE,
	Size,
};

struct Objective
{
	eObjectiveType myType;
	bool myIsDone;
	std::string myName;
};
