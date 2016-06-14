#include "stdafx.h"
#include "ObjectiveFactory.h"
#include <JsonWrapper/JsonWrapper.h>

ObjectiveFactory::ObjectiveFactory()
{
}


ObjectiveFactory::~ObjectiveFactory()
{

}

Objective* ObjectiveFactory::CreateObjective(eObjectiveType aType, std::string aDialogName)
{ 
	//This does nothing so far
	switch (aType)
	{
	case eObjectiveType::eLevelEnd:
		//objective;
		return new Objective;
	case eObjectiveType::eDialogMessage:
		return new Objective(aDialogName);
	default:
		DL_ASSERT(false, "Wrong ObjectiveType when creating objective");
		return new Objective;
	}
}