#include "GUIDialog.h"
#include "Message\DialogTextMessage.h"

GUIDialog::GUIDialog(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode) : myTextBox(aPosition, aDimensions, aFontPath, aMode)
{
	myIsEnabled = false;

	myTextBox.SetSize({ aDimensions.x - 24.f, aDimensions.y - 24.f });
	myTextBox.SetPosition({ aPosition.x + 12, aPosition.y + 12 });

	myTextBackground = new StaticSprite();
	myTextBackground->Init("Sprites/GUI/InGame/DialogBox/bg.dds", false, { 0, 0, 381, 214 }, {0, 0});
	myTextBackground->SetLayer(enumRenderLayer::eGUI);
	myPosition = aPosition;

	SingletonPostMaster::AddReciever(RecieverTypes::eDialogTextMessage, *this);
}

GUIDialog::~GUIDialog()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eDialogTextMessage, *this);
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
}

void
GUIDialog::Clear()
{
	myTextBox.Clear();
}

void
GUIDialog::Toggle()
{
	myIsEnabled = !myIsEnabled;
}

bool
GUIDialog::RecieveMessage(const DialogTextMessage& aMessage)
{
	myTextBox.Clear();
	myTextBox.AddText(aMessage.myText);
	Toggle();
	return true;
}