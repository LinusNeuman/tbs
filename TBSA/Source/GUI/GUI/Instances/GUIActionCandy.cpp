#include "GUIActionCandy.h"
#include <Message/CandyAmountMessage.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

GUIActionCandy::GUIActionCandy()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eCandyAmount, *this);
}


GUIActionCandy::~GUIActionCandy()
{
	SingletonPostMaster::RemoveReciever(*this);
}

void GUIActionCandy::WhenClicked()
{
	//if (myPlayerAP <= myCo)

	GUIAction::WhenClicked();

	if (myCanDoP1 == true)
	{
		if (myIsLocked == false)
		{
			SendPostMessage(GUIMessage(RecieverTypes::eEatCandy));
		}
	}
}

void GUIActionCandy::WhenHovered()
{
	GUIAction::WhenHovered();
}

bool GUIActionCandy::RecieveMessage(const CandyAmountMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eCandyAmount)
	{
		if (aMessage.myCandyAmount > 0)
		{
			myCanDoP1 = true;
			myCanDoP2 = true;
		}
		else
		{
			myCanDoP1 = false;
			myCanDoP2 = false;
		}
	}

	return true;
}

void GUIActionCandy::Init()
{
	CU::Vector2f position;
	position.x = 220;
	position.y = 901;
	
	position.x /= 1920;
	position.y /= 1080;

	position.x *= SingletonDataHolder::GetTargetResolution().x;
	position.y *= SingletonDataHolder::GetTargetResolution().y;

	Create("Sprites/GUI/Actions/Candy", position, 0, 0);
}
