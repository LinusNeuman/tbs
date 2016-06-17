#include "GUIActionCandy.h"
#include <Message/CandyAmountMessage.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>
#include <Rend/RenderConverter.h>
#include <Rend/RenderCommand.h>

GUIActionCandy::GUIActionCandy()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eCandyAmount, *this);
}


GUIActionCandy::~GUIActionCandy()
{
	SingletonPostMaster::RemoveReciever(*this);
	SAFE_DELETE(myCandyBag);
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

void GUIActionCandy::Render()
{
	GUIAction::Render();

	myCandyBag->Draw(myCandyBagPosition);

	TextRenderData data;
	data.myText = myCandyCountText->myText;
	data.myPos = myCandyCountTextPosition;
	data.myColor = {1,1,1,1};

	RenderConverter::AddRenderCommand(RenderCommand(1100.f, static_cast<unsigned short>(enumRenderLayer::eGUI), data));
//	RenderConverter::AddRenderCommandPutInCameraSpaceAndNormalize(RenderCommand(500.f, static_cast<unsigned short>(enumRenderLayer::eGUI), data));
}

bool GUIActionCandy::RecieveMessage(const CandyAmountMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eCandyAmount)
	{
		myCandyCountText->myText = std::to_string(aMessage.myCandyAmount);
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

	myCandyBag = new StaticSprite();
	myCandyBag->Init("Sprites/GUI/CandyCounter/CandyBag.dds", false, { 0, 0, 90, 74 });
	myCandyBag->SetLayer(enumRenderLayer::eGUI);

	myCandyBagPosition.x = 224;
	myCandyBagPosition.y = 985;
	myCandyBagPosition.x /= 1920;
	myCandyBagPosition.y /= 1080;

	myCandyBagPosition.x *= SingletonDataHolder::GetTargetResolution().x;
	myCandyBagPosition.y *= SingletonDataHolder::GetTargetResolution().y;

	myCandyCountTextPosition.x = 286;
	myCandyCountTextPosition.y = 1030;
	myCandyCountTextPosition.x /= 1920;
	myCandyCountTextPosition.y /= 1080;

	//myCandyCountTextPosition.x *= SingletonDataHolder::GetTargetResolution().x;
	//myCandyCountTextPosition.y *= SingletonDataHolder::GetTargetResolution().y;

	myCandyCountText = new DX2D::CText("Text/calibril.ttf_sdf");
	myCandyCountText->myText = "0";
}
