#include "GUIManager.h"
#include <Input/SingletoIsometricInputWrapper/SingletonIsometricInputWrapper.h>
#include <Message/MouseButtonPressedMessage.h>
#include <Message/MouseButtonDownMessage.h>
#include <Message/MouseButtonReleasedMessage.h>
#include <CU/Utility/CommonCasts.h>

GUIManager::GUIManager()
{
	myActiveGUI = nullptr;

	myHasPressed = false;
	myHasReleased = false;

	myRecieverOrder = RecieverOrder::eGUI;
	//SingletonPostMaster::AddReciever(RecieverTypes::eMouseInput, *this);// , RecieverOrder::eGUI);
}


GUIManager::~GUIManager()
{
	SingletonPostMaster::RemoveReciever(*this);

	if (myActiveGUI != nullptr)
	{
		myActiveGUI->DeleteAll();
	}
}

void GUIManager::Update(const CU::Time& aDelta)
{
	if (myActiveGUI == nullptr)
	{
		return;
	}

	for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
	{
		(*myActiveGUI)[ch]->Update(aDelta);
	}
}

void GUIManager::Render() const
{
	if (myActiveGUI == nullptr)
	{
		return;
	}

	for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
	{
		(*myActiveGUI)[ch]->Render();
	}
}

void GUIManager::LoadActiveGUI(CU::GrowingArray<GUIElement*, uchar>* anActiveGUI)
{
	myActiveGUI = anActiveGUI;
}

void GUIManager::StopRecieving()
{
	SingletonPostMaster::RemoveReciever(*this);
}

void GUIManager::StartRecieving()
{
	myRecieverOrder = RecieverOrder::eGUI;
	SingletonPostMaster::AddReciever(RecieverTypes::eMouseInput, *this);// , RecieverOrder::eGUI);
}

bool GUIManager::RecieveMessage(const MouseButtonDownMessage& aMessage)
{
	return true;
}

bool GUIManager::RecieveMessage(const MouseButtonPressedMessage& aMessage)
{
	if (myActiveGUI == nullptr)
	{
		return true;
	}
	bool shouldfuckoff = false;
	for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
	{
		if ((*myActiveGUI)[ch]->GetEnabled() == true)
		{
			if ((*myActiveGUI)[ch]->IsOver(IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
			{
				shouldfuckoff = true;
			}
		}
	}

	if (aMessage.myKey == USHORTCAST(CU::enumMouseButtons::eLeft) && aMessage.myKeyValue == true)
	{
		if (myHasReleased == false)
		{
			for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
			{
				if ((*myActiveGUI)[ch]->OnAction(eGUIMessageEvents::eOnDown, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
				{
				}
			}
		}
		
		myHasPressed = true;
	}
	else
	{
		myHasPressed = false;
	}
	if (shouldfuckoff == true)
	{
		return false;
	}
	return true;
}

bool GUIManager::RecieveMessage(const MouseButtonReleasedMessage& aMessage)
{
	if (myActiveGUI == nullptr)
	{
		return true;
	}
	bool shouldfuckoff = false;
	for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
	{
		if ((*myActiveGUI)[ch]->GetEnabled() == true)
		{
			if ((*myActiveGUI)[ch]->IsOver(IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
			{
				shouldfuckoff = true;
			}
		}
	}


	if (aMessage.myKey == USHORTCAST(CU::enumMouseButtons::eLeft) && aMessage.myKeyValue == true)
	{
		for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
		{
			if ((*myActiveGUI)[ch]->OnAction(eGUIMessageEvents::eOnClick, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
			{
			}
			if ((*myActiveGUI)[ch]->OnAction(eGUIMessageEvents::eOnUp, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
			{
				break;
			}
		}

		myHasReleased = true;
	}
	else
	{
		myHasReleased = false;
	}
	
	if (myHasReleased == false && myHasPressed == false)
	{
		for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
		{
			if ((*myActiveGUI)[ch]->OnAction(eGUIMessageEvents::eOnHover, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
			{
				break;
			}
		}
	}
	if (shouldfuckoff == true)
	{
		return false;
	}
	return true;
}