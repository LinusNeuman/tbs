#include "GUITextBox.h"
#include "Message\LogTextMessage.h"

GUITextBox::GUITextBox(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode) : myTextBox(aPosition, aDimensions, aFontPath, aMode)
{
	SingletonPostMaster::AddReciever(RecieverTypes::eLogText, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eClearLog, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eScrollLogDown, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eScrollLogUp, *this);
}

GUITextBox::~GUITextBox()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eLogText, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eClearLog, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eScrollLogDown, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eScrollLogUp, *this);
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

void
GUITextBox::Clear()
{
		myTextBox.Clear();
}

bool
GUITextBox::RecieveMessage(const LogTextMessage& aMessage)
{
	myTextBox.AddText(aMessage.myText);
	return true;
}

bool
GUITextBox::RecieveMessage(const ClearLogMessage& aMessage)
{
	myTextBox.Clear();
	return true;
}

bool
GUITextBox::RecieveMessage(const ScrollLogDownMessage& aMessage)
{
	myTextBox.ScrollDown();
	return true;
}

bool
GUITextBox::RecieveMessage(const ScrollLogUpMessage& aMessage)
{
	myTextBox.ScrollUp();
	return true;
}