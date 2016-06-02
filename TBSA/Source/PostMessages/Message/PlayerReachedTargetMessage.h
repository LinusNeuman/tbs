#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/Vector.h>

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerChangedTargetMessage : BaseMessage
{
	PlayerChangedTargetMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
	virtual ~PlayerChangedTargetMessage()
	{}

};
#pragma warning (pop)