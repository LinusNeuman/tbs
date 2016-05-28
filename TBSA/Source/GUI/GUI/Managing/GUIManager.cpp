#include "GUIManager.h"
#include <Input/SingletonIsometricInputWrapper.h>


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

	if (IsometricInput::GetMouseButtonPressed(CU::enumMouseButtons::eLeft) == true)
	{
		for (uchar ch = 0; ch < myActiveGUI->Size(); ++ch)
		{
			if ((*myActiveGUI)[ch]->OnAction(eGUIMessageEvents::eOnClick, IsometricInput::GetMouseWindowPositionNormalizedSpace()) == true)
			{
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
