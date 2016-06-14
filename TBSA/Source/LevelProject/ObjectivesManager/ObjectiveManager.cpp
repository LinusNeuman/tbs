﻿#include "stdafx.h"
#include "ObjectiveManager.h"
#include <PostMaster/SingletonPostMaster.h>
#include <JsonHelp/JsonHelp.h>
#include "Objectives/Objective.h"
#include <Message/BaseMessage.h>
#include <Message/TextMessage.h>
#include <Message/PositionMessage.h>
#include <Message/DialogTextMessage.h>
#include <../DialogLoader/DialogManager.h>

ObjectiveManager::ObjectiveManager()
{
#ifdef _DEBUG
	isConstructed = true;
#endif
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
#ifdef _DEBUG
	DL_ASSERT(isConstructed, "unconstructed object");
#endif

	myStages.RemoveAll();
	picojson::object root = JsonHelp::LoadJson(aPath);
	picojson::array stages = JsonHelp::GetArray(root["stages"]);

	myNextLevel = JsonHelp::GetString(root["nextLevel"]);

	myDialogs = LoadDialogs();

	for (size_t i = 0; i < stages.size(); i++)
	{
		picojson::array objectives = JsonHelp::GetArray(stages[i]);
		Stage stage;

		for (size_t j = 0; j < objectives.size(); j++)
		{
			picojson::object objectiveObject = JsonHelp::GetPicoJsonObject(objectives[j]);
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
#ifdef _DEBUG
	DL_ASSERT(isConstructed, "unconstructed object");
#endif
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

void ObjectiveManager::AddObjective(const int aIndex, std::string aName)
{
	myObjectives[aIndex] = aName;
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

	const Stage explaingStage = myStages[myCurrentStage];

	if (explaingStage.count(aMessage.myText))
	{
		if (myStages[myCurrentStage][aMessage.myText].myType == eLevelObjectiveType::HOLD)
		{
			completedObjectives[aMessage.myText] = myStages[myCurrentStage][aMessage.myText];
		}

		myStages[myCurrentStage].erase(aMessage.myText);
	}

	if (myDialogs.count(aMessage.myText))
	{
		SendPostMessage(DialogTextMessage(RecieverTypes::eDialogTextMessage, myDialogs[aMessage.myText]));
	}

	return true;
}

bool ObjectiveManager::RecieveMessage(const PositionMessage& aMessage)
{
	const int explainInt = 1000 * aMessage.myPosition.y + aMessage.myPosition.x;
	if (myObjectives.count(explainInt) > 0)
	{
		RecieveMessage(TextMessage(aMessage.myType, myObjectives[1000 * aMessage.myPosition.y + aMessage.myPosition.x]));
	}
	return true;
}
