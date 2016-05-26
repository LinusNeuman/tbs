void GUIElement::SetIsometric(bool aIsIsometric)
{
	myIsIsometric = aIsIsometric;
}

void GUIElement::SetEnabled(bool aIsEnabled)
{
	myIsEnabled = aIsEnabled;
}

void GUIElement::SetName(const char* aName)
{
	myName = aName;
}

void GUIElement::SetSprite(const char* aFilePath)
{
	mySprite = new StaticSprite();
	mySprite->Init(aFilePath, myIsIsometric);
}

void GUIElement::SetOnClick(GUIMessage* aGUIMessage)
{
	myMessageHandler.SetOnClick(aGUIMessage);
}

void GUIElement::SetOnHover(GUIMessage* aGUIMessage)
{
	myMessageHandler.SetOnHover(aGUIMessage);
}

void GUIElement::OnHover()
{
	myMessageHandler.Execute(eGUIMessageEvents::eOnHover);
}

void GUIElement::OnClick()
{
	myMessageHandler.Execute(eGUIMessageEvents::eOnClick);
}