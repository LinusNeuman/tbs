#pragma once

#include "RecieverTypes.h"
#include "BaseMessage.h"

#pragma warning (push)
#pragma warning (disable : 4512)

struct ClearLogMessage : public BaseMessage
{
	ClearLogMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
};

#pragma warning (pop)