void GUIElement::Create(const char* aName, const char* aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2i aWhiteSpaceInPixels, bool aIsIsometric = false, bool aIsEnabled = true)
{
	myName = aName;
	myIsIsometric = aIsIsometric;
	mySprite = new StaticSprite();
	mySprite->Init(
		aSpritePath, 
		myIsIsometric, 
		{	
			0.f, 0.f, 
			static_cast<float>(1.f - aWhiteSpaceInPixels.x), 
			static_cast<float>(1.f - aWhiteSpaceInPixels.y) 
		}
	);

	myParentSpace = aParentSpace;
	myPosition = aParentSpace + anOffset;
	myIsEnabled = aIsEnabled;

	myCollisionBox.SetWithMaxAndMinPos(
		myPosition,
		{
			myPosition.x + mySprite->GetSize().x,
			myPosition.y + mySprite->GetSize().y
		});
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