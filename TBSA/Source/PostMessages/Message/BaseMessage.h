#pragma once
#include "RecieverTypes.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct BaseMessage
{
	BaseMessage(const RecieverTypes aType) : myType(aType)
	{
		myLetThroughMessage = true;
	}
	virtual ~BaseMessage()
	{}

	const RecieverTypes myType;
	bool myLetThroughMessage;
};
#pragma warning (pop)