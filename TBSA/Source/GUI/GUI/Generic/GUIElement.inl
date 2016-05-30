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
	if (aMessageEvent == eGUIMessageEvents::eOnClick)
	{
		if (Intersection2D::PointInsideAABB2D(myCollisionBox, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
		{
			return myMessageHandler.Execute(aMessageEvent);
		}
	}
	if (aMessageEvent == eGUIMessageEvents::eOnHover)
	{
		if (Intersection2D::PointInsideAABB2D(myCollisionBox, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
		{
			myIsCurrentlyHovered = true;
			WhenHovered();
			return myMessageHandler.Execute(aMessageEvent);
		}
		else
		{
			if (myIsCurrentlyHovered == true)
			{
				myIsCurrentlyHovered = false;

				return myMessageHandler.Execute(eGUIMessageEvents::eOnLeave);
			}
		}
	}
	return false;
}