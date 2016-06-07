#pragma once

#include "GUI/Generic/GUIElement.h"
#include <TextBox.h>

class GUITextBox : public GUIElement
{
	public:
		GUITextBox(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode = eLinewrappingMode::Char);
		~GUITextBox();

		void Update(const CU::Time& aDeltaTime) override;
		void Render() override;

	private:
		TextBox myTextBox;
};

