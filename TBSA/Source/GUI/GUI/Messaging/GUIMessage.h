#pragma once
#include "../PostMessages/Message/BaseMessage.h"
#include <string>

class GUIMessage : public BaseMessage
{
public:
	GUIMessage(const RecieverTypes aType);
	~GUIMessage();

	//const std::string myEventString;
};

