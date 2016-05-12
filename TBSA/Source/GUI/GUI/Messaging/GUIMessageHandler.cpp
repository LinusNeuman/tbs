#include "GUIMessageHandler.h"


GUIMessageHandler::GUIMessageHandler()
{
}


GUIMessageHandler::~GUIMessageHandler()
{
}

void GUIMessageHandler::SetOnClick(GUIMessage& aGUIMessage)
{
	myMessageEvents[0] = aGUIMessage;
}

void GUIMessageHandler::SetOnHover(GUIMessage& aGUIMessage)
{
	myMessageEvents[1] = aGUIMessage;
}
