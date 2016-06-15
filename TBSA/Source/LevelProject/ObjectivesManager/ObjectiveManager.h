﻿// Author:   Hampus Huledal
// CreationDate: 09/06/2016
#pragma once
#include <PostMaster/MessageReceiver.h>
#include <map>
#include <queue>
#include "Objectives/Objective.h"
#include <CU/GrowingArray/GrowingArray.h>

struct TextMessage;
typedef std::map<std::string, LevelObjective> Stage;

class ObjectiveManager : public MessageReciever
{
public:

	ObjectiveManager();
	~ObjectiveManager();

	void LoadFromJson(std::string aPath);
	void Update();
	
	void AddObjective(int, std::string);
	int CountObjective(const std::string & aObjectiveName) const;
	const LevelObjective& GetObjective(const std::string& aObjectiveName);

	bool RecieveMessage(const TextMessage& aMessage) override;
	bool RecieveMessage(const PositionMessage& aMessage) override;
	bool RecieveMessage(const GUIMessage& aMessage) override;

private:
	bool dialogDone;
	bool dialogSent;
	bool levelDone;
	CommonUtilities::GrowingArray<Stage> myStages;
	Stage completedObjectives;
	unsigned short myCurrentStage;
	std::string myNextLevel;
	std::string myLevel;
	std::map<int, std::string> myObjectives;
	std::map<std::string, std::queue<std::string>> myDialogs;
#ifdef _DEBUG
	bool isConstructed;
#endif
};
