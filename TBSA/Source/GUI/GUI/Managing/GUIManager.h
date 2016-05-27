#pragma once

#include <GUI/Generic/GUIElement.h>

class GUIManager
{
public:
	GUIManager();
	~GUIManager();

	void Update();
	void Render() const;

	void LoadActiveGUI(CU::GrowingArray<GUIElement*, uchar>* anActiveGUI);
private:
	CU::GrowingArray<GUIElement*, uchar>* myActiveGUI;
};