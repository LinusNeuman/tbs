#pragma once

#include "BaseMessage.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct MouseInputClearMessage :public BaseMessage
{
	MouseInputClearMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
};
#pragma warning (pop)