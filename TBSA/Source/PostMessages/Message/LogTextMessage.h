#pragma once

#include <string>
#include "RecieverTypes.h"
#include "BaseMessage.h"

#pragma warning (push)
#pragma warning (disable : 4512)

struct LogTextMessage : public BaseMessage
{
	LogTextMessage(const RecieverTypes aType, const std::string& aMessage) : BaseMessage(aType)
	{
		myText = aMessage;
	}

	std::string myText;
};

#pragma warning (pop)