#include "GUITextBox.h"

GUITextBox::GUITextBox(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode) : myTextBox(aPosition, aDimensions, aFontPath, aMode)
{
	myTextBox.AddText("Här var det text!");
	myTextBox.AddText("Här var det lite mer text!");
	myTextBox.AddText("Här var det lite obscen text också: Röv och knark!!!");
}

GUITextBox::~GUITextBox()
{
}

void
GUITextBox::Render()
{
	myTextBox.Render();
}

void
GUITextBox::Update(const CU::Time& aTimeDelta)
{
	myTextBox.Update();
}