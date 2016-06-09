#include "stdafx.h"
#include "ObjectiveManager.h"
#include <PostMaster/SingletonPostMaster.h>
#include <JsonHelp/JsonHelp.h>

ObjectiveManager::ObjectiveManager()
{
	myStages.Init(1);
	myCurrentStage = 0;
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayEvents, *this);
}

ObjectiveManager::~ObjectiveManager()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::ePlayEvents, *this);
}

void ObjectiveManager::LoadFromJson(std::string aPath)
{
	picojson::object root = JsonHelp::LoadJson(aPath);
	picojson::array stages = JsonHelp::GetArray(root["stages"]);

	for (size_t i = 0; i < stages.size(); i++)
	{
		picojson::array objectives;
	}
}
