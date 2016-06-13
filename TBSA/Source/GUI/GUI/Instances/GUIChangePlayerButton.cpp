#include "GUIChangePlayerButton.h"
#include <Message/PlayerIDMessage.h>

GUIChangePlayerButton::GUIChangePlayerButton()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eClickedOnPlayer, *this);
}

GUIChangePlayerButton::~GUIChangePlayerButton()
{
	SingletonPostMaster::RemoveReciever(*this);
}

void GUIChangePlayerButton::Update(const CU::Time& aDelta)
{
	GUIButton::Update(aDelta);
}

void GUIChangePlayerButton::WhenClicked()
{
	++myPlayerID;
	if (myPlayerID > 1)
	{
		myPlayerID = 0;
	}
	SetAction(new PlayerIDMessage(RecieverTypes::eChangeSelectedPlayer, myPlayerID), eGUIMessageEvents::eOnClick);
}

void GUIChangePlayerButton::Render()
{
	GUIButton::Render();
}

bool GUIChangePlayerButton::RecieveMessage(const PlayerIDMessage& aMessage)
{
	myPlayerID = aMessage.myPlayerID;
	return true;
}
