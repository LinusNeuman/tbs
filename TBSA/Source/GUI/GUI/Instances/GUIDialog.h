#pragma once

#include "GUI/Generic/GUIElement.h"
#include <TextBox.h>

class GUIDialog : public GUIElement
{
public:
	GUIDialog(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode = eLinewrappingMode::Char);
	~GUIDialog();
	void Render() override;
	void Update(const CU::Time& aTimeDelta) override;
	void Clear();

private:
	TextBox myTextBox;
	//bool RecieveMessage(const DialogTextMessage& aMessage) override;
};

