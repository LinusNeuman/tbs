void GUIMessageHandler::SetAction(GUIMessage* aGUIMessage, eGUIMessageEvents aGUIMessageEvent)
{
	myMessageEvents[static_cast<int>(aGUIMessageEvent)] = aGUIMessage;
}

bool GUIMessageHandler::Execute(eGUIMessageEvents aGUIMessageEvent)
{
	if (myMessageEvents[static_cast<int>(aGUIMessageEvent)] != nullptr)
	{
		SingletonPostMaster::PostMessage(*myMessageEvents[static_cast<int>(aGUIMessageEvent)]);
		return true;
	}
	return false;
}