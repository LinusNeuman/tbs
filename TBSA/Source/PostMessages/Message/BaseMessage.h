#pragma once
#include "RecieverTypes.h"

struct BaseMessage
{
	BaseMessage(const RecieverTypes aType) : myType(aType)
	{}
	virtual ~BaseMessage()
	{}

	const RecieverTypes myType;
};