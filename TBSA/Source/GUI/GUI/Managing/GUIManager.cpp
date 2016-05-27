#include "GUIManager.h"
#include <Input/SingletonIsometricInputWrapper.h>


GUIManager::GUIManager()
{
	myActiveGUI = nullptr;
}


GUIManager::~GUIManager()
{
}

void GUIManager::Update()
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
