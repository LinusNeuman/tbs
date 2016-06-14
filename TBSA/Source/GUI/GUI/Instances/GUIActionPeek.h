#pragma once
#include "GUIAction.h"
class GUIActionPeek : public GUIAction
{
public:
	GUIActionPeek();
	~GUIActionPeek();

	virtual void WhenClicked() override;
	virtual void WhenHovered() override;

	virtual bool RecieveMessage(const PlayerPositionChangedMessage &aMessage) override;
	virtual bool RecieveMessage(const PlayerCanPeekMessage &aMessage) override;

	void Init();
};