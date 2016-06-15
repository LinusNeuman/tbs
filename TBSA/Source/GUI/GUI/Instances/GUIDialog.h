#pragma once

#include "GUI/Generic/GUIElement.h"
#include <TextBox.h>
#include <queue>

class GUIDialog : public GUIElement
{
	public:
		GUIDialog(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode = eLinewrappingMode::Char);
		~GUIDialog();
		void Render() override;
		void Update(const CU::Time& aTimeDelta) override;
		void SetLines(const unsigned int aLines);
		void Clear();
		void Toggle();

	private:
		TextBox myTextBox;
		StaticSprite* myTextBackground;
		StaticSprite* myPortrait;

		std::queue<std::string> myTexts;

		bool RecieveMessage(const DialogTextMessage& aMessage) override;
};

