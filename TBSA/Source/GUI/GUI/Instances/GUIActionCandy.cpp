#include "GUIActionCandy.h"
#include <Message/CandyAmountMessage.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>
#include <Rend/RenderConverter.h>
#include <Rend/RenderCommand.h>
#include "Message/SendApSuggestion.h"

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
	if (myCanDoP1 == true)
	{
		SendPostMessage(SendAPSuggestionMessage(RecieverTypes::eSuggestAPChange, 2))
	}
}

void GUIActionCandy::Render()
{
	GUIAction::Render();

	
//	RenderConverter::AddRenderCommandPutInCameraSpaceAndNormalize(RenderCommand(500.f, static_cast<unsigned short>(enumRenderLayer::eGUI), data));
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

	Create("Sprites/GUI/Actions/Candy", position, 0, 0, "Eat candy to gain extra AP for the selected character.\nCost: 1 Candy. Shortcut: Q", {365, 64});
}
