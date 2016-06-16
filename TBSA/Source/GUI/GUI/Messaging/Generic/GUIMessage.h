#pragma once
#include <Message/BaseMessage.h>
#include <string>

#pragma warning  (push)
#pragma warning(disable : 4512)

struct GUIMessage : public BaseMessage
{
	GUIMessage(const RecieverTypes aType);
	~GUIMessage();

	//const std::string myEventString;
};

#pragma warning (pop)