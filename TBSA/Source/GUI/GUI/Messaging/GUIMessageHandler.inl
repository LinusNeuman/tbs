void GUIMessageHandler::SetAction(GUIMessage* aGUIMessage, eGUIMessageEvents aGUIMessageEvent)
{
	myMessageEvents[static_cast<int>(aGUIMessageEvent)] = aGUIMessage;
}

bool GUIMessageHandler::Execute(eGUIMessageEvents aGUIMessageEvent)
{
	SingletonPostMaster::PostMessage(*myMessageEvents[static_cast<int>(aGUIMessageEvent)]);
	return true;
}