#pragma once
#include "GUIAction.h"
#include <tga2d/text/text.h>

class GUIActionCandy : public GUIAction
{
public:
	GUIActionCandy();
	~GUIActionCandy();

	virtual void WhenClicked() override;
	virtual void WhenHovered() override;

	virtual void Render() override;

	virtual bool RecieveMessage(const CandyAmountMessage &aMessage) override;

	void Init();
private:

};
