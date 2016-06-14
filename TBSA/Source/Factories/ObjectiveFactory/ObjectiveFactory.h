#pragma once

#include "Objective.h"

class ObjectiveFactory
{
public:
	ObjectiveFactory();
	~ObjectiveFactory();
	Objective* CreateObjective(eObjectiveType aType, std::string aDialogName = "");
private:

};