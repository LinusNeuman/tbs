bool GUIElement::GetIsHovered()
{
	return myIsCurrentlyHovered;
}

void GUIElement::SetAction(GUIMessage* aGUIMessage, eGUIMessageEvents aMessageEvent)
{
	myMessageHandler.SetAction(aGUIMessage, aMessageEvent);
}

bool GUIElement::OnAction(eGUIMessageEvents aMessageEvent, CU::Vector2f aMousePosition)
{
	(aMousePosition);
	if (aMessageEvent == eGUIMessageEvents::eOnClick)
	{
		if (Intersection2D::PointInsideAABB2D(myCollisionBox, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
		{
			WhenClicked();
			return myMessageHandler.Execute(aMessageEvent);
		}
	}
	if (aMessageEvent == eGUIMessageEvents::eOnDown)
	{
		if (Intersection2D::PointInsideAABB2D(myCollisionBox, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
		{
			myIsCurrentlyPressed = true;
			return myMessageHandler.Execute(aMessageEvent);
		}
	}
	if (aMessageEvent == eGUIMessageEvents::eOnUp)
	{
		if (myIsCurrentlyPressed == true)
		{
			myIsCurrentlyPressed = false;
			return myMessageHandler.Execute(eGUIMessageEvents::eOnUp);
		}
	}
	if (aMessageEvent == eGUIMessageEvents::eOnHover)
	{
		if (Intersection2D::PointInsideAABB2D(myCollisionBox, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
		{
			
			WhenHovered();
			myIsCurrentlyHovered = true;
			return myMessageHandler.Execute(aMessageEvent);
		}
		if (myIsCurrentlyHovered == true)
		{
			myIsCurrentlyHovered = false;

			return myMessageHandler.Execute(eGUIMessageEvents::eOnLeave);
		}
	}
	return false;
}