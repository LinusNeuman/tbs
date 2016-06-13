#include "GUIDialog.h"
#include "Message\LogTextMessage.h"

GUIDialog::GUIDialog(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode) : myTextBox(aPosition, aDimensions, aFontPath, aMode)
{
	myIsEnabled = true;

	myTextBox.SetSize(aDimensions);
	myTextBox.SetPosition(aPosition);
	myTextBox.AddText("Wee!");

	myTextBackground = new StaticSprite();
	myTextBackground->Init("Sprites/GUI/InGame/DialogBox/bg.dds", false, { 0, 0, 381, 214 }, {0, 0});
	myTextBackground->SetLayer(enumRenderLayer::eGUI);
	myPosition = aPosition;
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
		myTextBackground->Draw(myPosition);
		myTextBox.Render();
	}
}

void
GUIDialog::Update(const CU::Time& aTimeDelta)
{
	myTextBox.Update();

	if (IsometricInput::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft) == true)
	{
		myIsEnabled = !myIsEnabled;
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