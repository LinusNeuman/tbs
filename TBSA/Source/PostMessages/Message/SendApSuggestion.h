#pragma once

#include "Message/BaseMessage.h"
#include <windows.h>


#pragma warning  (push)
#pragma warning(disable : 4512)
struct SendAPSuggestionMessage : public BaseMessage
{
	SendAPSuggestionMessage(const RecieverTypes aRecieverType, const unsigned short aAPValue)
		: BaseMessage(aRecieverType),
		myAPSuggestion(aAPValue)
	{
	}

	const unsigned short myAPSuggestion;
};
#pragma warning (pop)