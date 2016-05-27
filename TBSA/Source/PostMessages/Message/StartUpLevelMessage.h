#pragma once
#include <string>
#include "BaseMessage.h"
#pragma warning  (push)
#pragma warning(disable : 4512)

struct StartUpLevelMessage : BaseMessage
{
	StartUpLevelMessage(const RecieverTypes aRecieverType, const std::string &aPath) :
		BaseMessage(aRecieverType),
		myPath(aPath)
	{}

		const std::string myPath;
};
#pragma warning (pop)