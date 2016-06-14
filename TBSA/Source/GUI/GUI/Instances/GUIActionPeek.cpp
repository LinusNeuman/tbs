#include "GUIActionPeek.h"
#include <Message/PlayerCanPeekMessage.h>
#include <Message/PlayerPositionChangedMessage.h>

GUIActionPeek::GUIActionPeek()
{
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayerPositionChanged, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayerCanPeek, *this);
}


GUIActionPeek::~GUIActionPeek()
{
	SingletonPostMaster::RemoveReciever(*this);
}

void GUIActionPeek::WhenClicked()
{
	//if (myPlayerAP <= myCo)

	GUIAction::WhenClicked();
}

void GUIActionPeek::WhenHovered()
{
	GUIAction::WhenHovered();
}

bool GUIActionPeek::RecieveMessage(const PlayerPositionChangedMessage& aMessage)
{
	myCanDo = false;
	return true;
}

bool GUIActionPeek::RecieveMessage(const PlayerCanPeekMessage& aMessage)
{
	myCanDo = true;
	return true;
}

void GUIActionPeek::Init()
{
	Create("Sprites/GUI/Actions/Peek", { 220, 854 }, 2, 1);
}
