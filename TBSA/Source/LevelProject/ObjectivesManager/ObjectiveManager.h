// Author:   Hampus Huledal
// CreationDate: 09/06/2016
#pragma once
#include <Objective.h>
#include <PostMaster/MessageReceiver.h>
#include <map>

typedef std::map<std::string, Objective> Stage;

class ObjectiveManager : public MessageReciever
{
public:
	ObjectiveManager();
	~ObjectiveManager();

	void LoadFromJson(std::string aPath);
	void Update();

private:
	CommonUtilities::GrowingArray<Stage> myStages;
	unsigned short myCurrentStage;
};
