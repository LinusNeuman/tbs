#pragma once
#include "GUIAction.h"
class GUIActionCandy : public GUIAction
{
public:
	GUIActionCandy();
	~GUIActionCandy();

	virtual void WhenClicked() override;
	virtual void WhenHovered() override;

	virtual bool RecieveMessage(const CandyAmountMessage &aMessage) override;

	void Init();
};