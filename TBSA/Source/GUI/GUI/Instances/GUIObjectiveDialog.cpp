#include "GUIObjectiveDialog.h"
//#include "Message\ObjectiveTextMessage.h"

GUIObjectiveDialog::GUIObjectiveDialog(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode) : myTextBox(aPosition, aDimensions, aFontPath, aMode)
{
	myIsEnabled = false;

	myTextBox.SetSize({ aDimensions.x - 24.f, aDimensions.y - 24.f });
	myTextBox.SetPosition({ aPosition.x + 12, aPosition.y + 12 });

	myTextBackground = new StaticSprite();
	myTextBackground->Init("Sprites/GUI/InGame/DialogBox/bg.dds", false, { 0, 0, 381, 214 }, { 0, 0 });
	myTextBackground->SetLayer(enumRenderLayer::eGUI);
	myPosition = aPosition;

	//SingletonPostMaster::AddReciever(RecieverTypes::eDialogTextMessage, *this);
}

GUIObjectiveDialog::~GUIObjectiveDialog()
{
	//SingletonPostMaster::RemoveReciever(RecieverTypes::eDialogTextMessage, *this);
}

void
GUIObjectiveDialog::SetLines(const unsigned int aLines)
{
	myTextBox.SetLines(aLines);
}

void
GUIObjectiveDialog::Render()
{
	myTextBackground->Draw(myPosition);
	myTextBox.Render();
}

void
GUIObjectiveDialog::Update(const CU::Time& aTimeDelta)
{
	if (myIsEnabled == false && myTexts.size() > 0)
	{
		myIsEnabled = true;
		myTextBox.Clear();
		myTextBox.AddText(myTexts.front());
		myTexts.pop();
	}

	if (myIsEnabled == true)
	{
		if (SingletonIsometricInputWrapper::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft) == true)
		{
			if (myTexts.size() == 0)
			{
				myIsEnabled = false;
			}
			else
			{
				myTextBox.Clear();
				myTextBox.AddText(myTexts.front());
				myTexts.pop();
			}
		}
	}

	myTextBox.Update();
}

void
GUIObjectiveDialog::Clear()
{
	myTextBox.Clear();
}

void
GUIObjectiveDialog::Toggle()
{
	myIsEnabled = !myIsEnabled;
}

//bool
//GUIObjectiveDialog::RecieveMessage(const ObjectiveTextMessage& aMessage)
//{
//	myTexts = aMessage.myTexts;
//
//	return true;
//}