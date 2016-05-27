#include "GUIMessageHandler.h"


GUIMessageHandler::GUIMessageHandler()
{
}


GUIMessageHandler::~GUIMessageHandler()
{
	for (int i = 0; i < static_cast<int>(eGUIMessageEvents::eEnumLength); ++i)
	{
		delete myMessageEvents[i];
	}
}