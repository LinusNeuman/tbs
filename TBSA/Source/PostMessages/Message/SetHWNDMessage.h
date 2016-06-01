#pragma once

#include "Message/BaseMessage.h"
#include <windows.h>


#pragma warning  (push)
#pragma warning(disable : 4512)
struct SetHWNDMessage : public BaseMessage
{
	SetHWNDMessage(const RecieverTypes aRecieverType, const HWND & aWindowHandle)
		: BaseMessage(aRecieverType),
		myWindowHandle(aWindowHandle)
	{
	}

	const HWND & myWindowHandle;
};
#pragma warning (pop)