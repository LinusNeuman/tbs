#pragma once
#include <GUI/Generic/GUIElement.h>
class GUIActionPointsBar : public GUIElement
{
public:
	GUIActionPointsBar();
	~GUIActionPointsBar();

	void WhenHovered() override;
	void WhenClicked() override;
	void WhenLeaved() override;

	void Update(const CU::Time &aDelta) override;

	//void RecieveMessage(const BaseM)
private:
	
};