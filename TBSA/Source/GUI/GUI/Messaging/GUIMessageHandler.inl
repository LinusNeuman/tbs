void GUIMessageHandler::SetOnClick(GUIMessage* aGUIMessage)
{
	myMessageEvents[0] = aGUIMessage;
}

void GUIMessageHandler::SetOnHover(GUIMessage* aGUIMessage)
{
	myMessageEvents[1] = aGUIMessage;
}

void GUIMessageHandler::Execute(eGUIMessageEvents aGUIMessageEvent)
{
	SingletonPostMaster::PostMessage(*myMessageEvents[static_cast<int>(aGUIMessageEvent)]);
}