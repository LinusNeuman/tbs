#include "GUIActionPeek.h"
#include <Message/PlayerCanPeekMessage.h>
#include <Message/PlayerPositionChangedMessage.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

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

	if (mySelectedPlayer == 0)
	{
		if (myCanDoP1 == true)
		{
			if (myIsLocked == false)
			{
				SendPostMessage(BaseMessage(RecieverTypes::ePlayerIsPeeking));
			}
		}
	}
	if (mySelectedPlayer == 1)
	{
		if (myCanDoP2 == true)
		{
			if (myIsLocked == false)
			{
				SendPostMessage(BaseMessage(RecieverTypes::ePlayerIsPeeking));
			}
		}
	}
}

void GUIActionPeek::WhenHovered()
{
	GUIAction::WhenHovered();
}

bool GUIActionPeek::RecieveMessage(const PlayerPositionChangedMessage& aMessage)
{
	if (aMessage.myPlayerID == 0)
	{
		myCanDoP1 = false;
		return true;
	}
	
	myCanDoP2 = false;
	return true;
}

bool GUIActionPeek::RecieveMessage(const PlayerCanPeekMessage& aMessage)
{
	if (aMessage.myPlayerID == 0)
	{
		myCanDoP1 = true;
		return true;
	}

	myCanDoP2 = true;
	return true;
}

void GUIActionPeek::Init()
{
	CU::Vector2f position;
	position.x = 220;
	position.y = 854;
	

	position.x /= 1920;
	position.y /= 1080;

	position.x *= SingletonDataHolder::GetTargetResolution().x;
	position.y *= SingletonDataHolder::GetTargetResolution().y;

	Create("Sprites/GUI/Actions/Peek", position, 2, 1);
}
