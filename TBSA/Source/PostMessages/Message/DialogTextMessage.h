#pragma once

#include <string>
#include <queue>
#include "RecieverTypes.h"
#include "BaseMessage.h"

#pragma warning (push)
#pragma warning (disable : 4512)

struct DialogTextMessage : public BaseMessage
{
	DialogTextMessage(const RecieverTypes aType, const std::queue<std::string> aMessage) : BaseMessage(aType)
	{
		myTexts = aMessage;
	}

	std::queue<std::string> myTexts;
};

#pragma warning (pop)