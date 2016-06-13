#pragma once

#include <GUI/Messaging/Generic/GUIMessage.h>

#pragma warning  (push)
#pragma warning(disable : 4512)
struct PlayerIDMessage : public GUIMessage
{
	PlayerIDMessage(const RecieverTypes aRecieverType, const unsigned short aPlayerID)
		: GUIMessage(aRecieverType),
		myPlayerID(aPlayerID)
	{
	}

	const unsigned short myPlayerID;
};
#pragma warning (pop)