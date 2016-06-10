#include "GUIDialog.h"
#include "Message\LogTextMessage.h"

GUIDialog::GUIDialog(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode) : myTextBox(aPosition, aDimensions, aFontPath, aMode)
{
	myIsEnabled = true;
	//SingletonPostMaster::AddReciever(RecieverTypes::eDialogText, *this);
}

GUIDialog::~GUIDialog()
{
	//SingletonPostMaster::RemoveReciever(RecieverTypes::eDialogText, *this);
}

void
GUIDialog::Render()
{
	if (myIsEnabled == true)
	{
		myTextBox.Render();
	}
}

void
GUIDialog::Update(const CU::Time& aTimeDelta)
{
	myTextBox.Update();

	if (myIsEnabled == true)
	{
		if (IsometricInput::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft) == true)
		{
			myIsEnabled = false;
		}
	}
}

void
GUIDialog::Clear()
{
	myTextBox.Clear();
}

//bool
//GUIDialog::RecieveMessage(const DialogTextMessage& aMessage)
//{
//	myTextBox.Clear();
//	myTextBox.AddText(aMessage.myText);
//	return true;
//}