#include "GUITextBox.h"
#include "Message\LogTextMessage.h"

GUITextBox::GUITextBox(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode) : myTextBox(aPosition, aDimensions, aFontPath, aMode)
{
	SingletonPostMaster::AddReciever(RecieverTypes::eLogText, *this);
}

GUITextBox::~GUITextBox()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eLogText, *this);
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

bool
GUITextBox::RecieveMessage(const LogTextMessage& aMessage)
{
	myTextBox.AddText(aMessage.myText);
	return true;
}