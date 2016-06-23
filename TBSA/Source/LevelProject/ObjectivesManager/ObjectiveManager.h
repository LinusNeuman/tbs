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

	void Init();
	void AddAsReciever();
	
	void UpdateObjectiveBox();
	static std::string GetObjectiveDescription(const LevelObjective & aLevelObjective);

	void AddObjective(int, std::string);
	int CountObjective(const std::string & aObjectiveName) const;
	const LevelObjective& GetObjective(const std::string& aObjectiveName);
	Stage GetCurrentStage();

	bool RecieveMessage(const TextMessage& aMessage) override;
	bool RecieveMessage(const PositionMessage& aMessage) override;
	bool RecieveMessage(const GUIMessage& aMessage) override;

	bool GetIsInitialized() const;
	bool GetShouldLoadData() const;
	void SetShouldLoadData(const bool aLoadDataFlag);

private:
	bool myIShouldLoadData;
	bool myIsInitialized;
	bool dialogDone;
	bool dialogSent;
	bool levelDone;
	bool startDialogSent;
	CommonUtilities::GrowingArray<Stage> myStages;
	Stage completedObjectives;
	unsigned short myCurrentStage;
	std::string myNextLevel;
	std::string myLevel;
	std::map<int, std::string> myObjectives;
	std::map<std::string, std::queue<std::string>> myDialogs;

	CommonUtilities::GrowingArray<std::string> myStageEndDialogs;
};

inline bool ObjectiveManager::GetIsInitialized() const
{
	return myIsInitialized;
}

inline bool ObjectiveManager::GetShouldLoadData() const
{
	return myIShouldLoadData;
}

inline void ObjectiveManager::SetShouldLoadData(const bool aLoadDataFlag)
{
	myIShouldLoadData = aLoadDataFlag;
}