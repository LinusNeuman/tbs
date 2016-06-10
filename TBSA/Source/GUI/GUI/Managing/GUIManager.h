#pragma once

#include <GUI/Generic/GUIElement.h>

class GUIManager : public MessageReciever
{
public:
	GUIManager();
	~GUIManager();

	void Update(const CU::Time& aDelta);
	void Render() const;

	void LoadActiveGUI(CU::GrowingArray<GUIElement*, uchar>* anActiveGUI);

	bool RecieveMessage(const MouseButtonDownMessage& aMessage) override;
	bool RecieveMessage(const MouseButtonPressedMessage& aMessage) override;
	bool RecieveMessage(const MouseButtonReleasedMessage& aMessage) override;
private:
	CU::GrowingArray<GUIElement*, uchar>* myActiveGUI;

	bool myHasPressed;
	bool myHasReleased;
};