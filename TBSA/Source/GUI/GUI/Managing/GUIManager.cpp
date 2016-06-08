#include "GUIManager.h"
#include <Input/SingletoIsometricInputWrapper/SingletonIsometricInputWrapper.h>

GUIManager::GUIManager()
{
	myActiveGUI = nullptr;
}


GUIManager::~GUIManager()
{
}

void GUIManager::Update(const CU::Time& aDelta)
{
	if (myActiveGUI == nullptr)
	{
		return;
	}

	if (IsometricInput::GetMouseButtonReleased(CU::enumMouseButtons::eLeft) == true)
	{
		for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
		{
			if ((*myActiveGUI)[ch]->OnAction(eGUIMessageEvents::eOnClick, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
			{
				(*myActiveGUI)[ch]->Update(aDelta);
			}
			if ((*myActiveGUI)[ch]->OnAction(eGUIMessageEvents::eOnUp, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
			{
				(*myActiveGUI)[ch]->Update(aDelta);
				break;
			}
		}
	}
	else if (IsometricInput::GetMouseButtonPressed(CU::enumMouseButtons::eLeft) == true)
	{
		for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
		{
			if ((*myActiveGUI)[ch]->OnAction(eGUIMessageEvents::eOnDown, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
			{
				(*myActiveGUI)[ch]->Update(aDelta);
				break;
			}
		}
	}
	else
	{
		for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
		{
			if ((*myActiveGUI)[ch]->OnAction(eGUIMessageEvents::eOnHover, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
			{
				(*myActiveGUI)[ch]->Update(aDelta);
				break;
			}
		}
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
