#include "stdafx.h"
#include "ObjectiveFactory.h"
#include <JsonWrapper/JsonWrapper.h>

ObjectiveFactory::ObjectiveFactory()
{
}


ObjectiveFactory::~ObjectiveFactory()
{

}

Objective* ObjectiveFactory::CreateObjective(eObjectiveType aType)
{ 
	//This does nothing so far
	Objective* objective = new Objective();
	switch (aType)
	{
	case eObjectiveType::eLevelEnd:
		objective;
		return objective;
	default:
		DL_ASSERT(false, "Wrong ObjectiveType when creating objective");
		return objective;
	}
}