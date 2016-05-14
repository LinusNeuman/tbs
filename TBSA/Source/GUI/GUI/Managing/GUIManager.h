#pragma once

#include <GUI/Generic/GUIElement.h>

class GUIManager
{
public:
	GUIManager();
	~GUIManager();

private:
	CU::GrowingArray<GUIElement*, uchar> myActiveGUI;
};

