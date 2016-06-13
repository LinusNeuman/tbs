#pragma once
#include "Message/BaseMessage.h"

#pragma warning  (push)
#pragma warning(disable : 4512)

class CreditScreenMessage : public GUIMessage
{
public:
	CreditScreenMessage(const RecieverTypes aRecieverType)
		: GUIMessage(aRecieverType)
	{
	}
};
#pragma warning (pop)
