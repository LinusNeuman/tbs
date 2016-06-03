#pragma once
#include <string>
#include "RecieverTypes.h"
#include "BaseMessage.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct GoalReachedMessage : public BaseMessage
{
	GoalReachedMessage(const RecieverTypes aType, const std::string & aLevelNamePath ) : BaseMessage(aType), aLevelPathNameToChangeTo(aLevelNamePath)
	{}
	virtual ~GoalReachedMessage()
	{}

	const std::string & aLevelPathNameToChangeTo;
};
#pragma warning (pop)