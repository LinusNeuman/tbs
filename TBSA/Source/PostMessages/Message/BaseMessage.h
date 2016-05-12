#pragma once
#include "RecieverTypes.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct BaseMessage
{
	BaseMessage(const RecieverTypes aType) : myType(aType)
	{}
	virtual ~BaseMessage()
	{}

	const RecieverTypes myType;
};
#pragma warning (pop)