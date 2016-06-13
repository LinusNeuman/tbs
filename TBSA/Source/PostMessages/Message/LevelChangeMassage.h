#pragma once
#include "Message/BaseMessage.h"

#pragma warning  (push)
#pragma warning(disable : 4512)

struct LevelChangeMassage : public GUIMessage
{
	LevelChangeMassage(const RecieverTypes aRecieverType, const unsigned short aLevel)
		: GUIMessage(aRecieverType),
		myLevel(aLevel)
	{
	}

	const unsigned short myLevel;
};
#pragma warning (pop)