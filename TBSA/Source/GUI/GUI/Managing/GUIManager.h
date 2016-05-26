#pragma once

#include <GUI/Generic/GUIElement.h>

class GUIManager
{
public:
	GUIManager();
	~GUIManager();

	void Update();
private:
	CU::GrowingArray<GUIElement*, uchar>* myActiveGUI;
};