#include "stdafx.h"
#include "ObjectiveManager.h"
#include <PostMaster/SingletonPostMaster.h>
#include <JsonHelp/JsonHelp.h>
#include "Objectives/Objective.h"
#include <Message/BaseMessage.h>
#include <Message/TextMessage.h>

ObjectiveManager::ObjectiveManager()
{
	myStages.Init(1);
	myCurrentStage = 0;
	SingletonPostMaster::AddReciever(RecieverTypes::eObjctive, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eLeaveObjective, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eEnemyDied, *this);
}

ObjectiveManager::~ObjectiveManager()
{
	SingletonPostMaster::RemoveReciever( *this);
}

void ObjectiveManager::LoadFromJson(std::string aPath)
{
	myStages.RemoveAll();
	picojson::object root = JsonHelp::LoadJson(aPath);
	picojson::array stages = JsonHelp::GetArray(root["stages"]);

	for (size_t i = 0; i < stages.size(); i++)
	{
		picojson::array objectives = JsonHelp::GetArray(stages[i]);
		Stage stage;

		for (size_t j = 0; j < objectives.size(); j++)
		{
			picojson::object objectiveObject = JsonHelp::GetObject(objectives[j]);
			LevelObjective objective;

			objective.myTarget = JsonHelp::GetString(objectiveObject["target"]);
			objective.myIsDone = false;

			const std::string typeString = JsonHelp::GetString(objectiveObject["type"]);

			if (typeString == "kill")
			{
				objective.myType = eLevelObjectiveType::KILL;
			}
			else if (typeString == "hold_objective")
			{
				objective.myType = eLevelObjectiveType::HOLD;
			}
			else if (typeString == "take_objective")
			{
				objective.myType = eLevelObjectiveType::TAKE;
			}
			else
			{
				DL_ASSERT(false, ("Error in objective file " + aPath + ": " + typeString + " Is not a valid objective type").c_str());
				objective.myType = eLevelObjectiveType::Size;
			}

			stage[objective.myTarget] = objective;
		}
		myStages.Add(stage);
	}
}

void ObjectiveManager::Update()
{
	if (myStages[myCurrentStage].size() < 1)
	{
		completedObjectives.clear();
		++myCurrentStage;
		if (myCurrentStage >= myStages.Size())
		{
			SendPostMessage(TextMessage(RecieverTypes::eLevelEnd, myNextLevel))
		}
	}
}

bool ObjectiveManager::RecieveMessage(const TextMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eLeaveObjective)
	{
		if (completedObjectives.count(aMessage.myText) && completedObjectives[aMessage.myText].myType == eLevelObjectiveType::HOLD)
		{
			myStages[myCurrentStage][aMessage.myText] = completedObjectives[aMessage.myText];
		}
		return true;
	}

	if (myStages[myCurrentStage].count(aMessage.myText))
	{
		if (myStages[myCurrentStage][aMessage.myText].myType == eLevelObjectiveType::HOLD)
		{
			completedObjectives[aMessage.myText] = myStages[myCurrentStage][aMessage.myText];
		}

		myStages[myCurrentStage].erase(aMessage.myText);
	}
	return true;
}
