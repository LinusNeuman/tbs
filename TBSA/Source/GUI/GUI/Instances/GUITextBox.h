#pragma once

#include "GUI/Generic/GUIElement.h"
#include <TextBox.h>

class GUITextBox : public GUIElement
{
	public:
		GUITextBox(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode = eLinewrappingMode::Char);
		~GUITextBox();

		void Render() override;
		void Update(const CU::Time& aTimeDelta) override;
		void Clear();

	private:
		TextBox myTextBox;

		bool RecieveMessage(const LogTextMessage& aMessage) override;
		bool RecieveMessage(const ClearLogMessage& aMessage) override;
		bool RecieveMessage(const ScrollLogDownMessage& aMessage) override;
		bool RecieveMessage(const ScrollLogUpMessage& aMessage) override;
};

