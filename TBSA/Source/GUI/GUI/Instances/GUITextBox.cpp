#include "GUITextBox.h"

GUITextBox::GUITextBox(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode) : myTextBox(aPosition, aDimensions, aFontPath, aMode)
{
	myTextBox.AddText("H�r var det text!");
	myTextBox.AddText("H�r var det lite mer text!");
	myTextBox.AddText("H�r var det lite obscen text ocks�: R�v och knark!!!");
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