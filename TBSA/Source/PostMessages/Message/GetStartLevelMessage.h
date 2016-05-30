#pragma once
#include "RecieverTypes.h"
#include "BaseMessage.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct GetStartLevelMessage: public BaseMessage
{
	GetStartLevelMessage(const RecieverTypes aType) : BaseMessage(aType), myType(aType)
	{}
	virtual ~GetStartLevelMessage()
	{}

	const RecieverTypes myType;
};
#pragma warning (pop)