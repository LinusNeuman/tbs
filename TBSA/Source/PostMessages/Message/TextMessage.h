#pragma once

#include <string>
#include "RecieverTypes.h"
#include "BaseMessage.h"

#pragma warning (push)
#pragma warning (disable : 4512)

struct TextMessage : public BaseMessage
{// aka sms here you can send sexy stuff and emojis :smile: :eggplant:
	TextMessage(const RecieverTypes aType, const std::string& aMessage) : BaseMessage(aType)
	{
		myText = aMessage;
	}

	std::string myText;
};

#pragma warning (pop)