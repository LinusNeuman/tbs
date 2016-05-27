void GUIElement::Create(const char* aName, const char* aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, bool aIsIsometric = false, bool aIsEnabled = true)
{
	myName = aName;
	mySprite = new StaticSprite();
	mySprite->Init(aSpritePath);
	myParentSpace = aParentSpace;
	myPosition = aParentSpace + anOffset;
	myIsIsometric = aIsIsometric;
	myIsEnabled = aIsEnabled;

	myCollisionBox.SetWithMaxAndMinPos(
		myPosition,
		{
			myPosition.x + mySprite->GetSize().x,
			myPosition.y + mySprite->GetSize().y
		});
}

void GUIElement::SetParentSpace(CU::Vector2f aParentSpace)
{
	myParentSpace = aParentSpace;
	myCollisionBox.SetPosition(aParentSpace);
}

void GUIElement::SetPosition(CU::Vector2f aPosition)
{
	myPosition = aPosition;
	myCollisionBox.SetPosition(myPosition + myParentSpace);
}

void GUIElement::SetSize(CU::Vector2f aSize)
{
	mySize = aSize;
	myCollisionBox.SetSize(mySize);
}

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

void GUIElement::SetAction(GUIMessage* aGUIMessage, eGUIMessageEvents aMessageEvent)
{
	myMessageHandler.SetAction(aGUIMessage, aMessageEvent);
}

bool GUIElement::OnAction(eGUIMessageEvents aMessageEvent, CU::Vector2f aMousePosition)
{
	if (aMessageEvent == eGUIMessageEvents::eOnClick)
	{
		if (Intersection2D::PointInsideAABB2D(myCollisionBox, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
		{
			return myMessageHandler.Execute(aMessageEvent);
		}
	}
	return false;
}