#include "GUICandyCounter.h"
#include <Rend/RenderConverter.h>
#include <Rend/RenderCommand.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

GUICandyCounter::GUICandyCounter()
{
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

	myTooltip.Init("Your candy bag. Search for candy around the map.", { 350, 20 }, 0.5f, 0.005f);

	SingletonPostMaster::AddReciever(RecieverTypes::eCandyAmount, *this);

	CU::Vector2f boxPosition = { myCandyBagPosition.x / SingletonDataHolder::GetTargetResolutionf().x, myCandyBagPosition.y / SingletonDataHolder::GetTargetResolutionf().y };
	CU::Vector2f spriteSizeNorm = { FLOATCAST(myCandyBag->GetSizeInPixels().x) / (1920.f), FLOATCAST(myCandyBag->GetSizeInPixels().y) / (1080.f) };

	myCollisionBox.SetWithMaxAndMinPos(
		boxPosition,
		{
			boxPosition.x + spriteSizeNorm.x,
			boxPosition.y + spriteSizeNorm.y
		});
}


GUICandyCounter::~GUICandyCounter()
{
	SAFE_DELETE(myCandyBag);
	SingletonPostMaster::RemoveReciever(*this);
}

void GUICandyCounter::Create(const std::string& aSpritePath, CU::Vector2f aPosition, int aCost1, int aCost2, const char* aTooltip, CU::Vector2i aTooltipSize)
{

}

void GUICandyCounter::Update(const CU::Time& aDelta)
{
	myTooltip.Update(aDelta);
}

void GUICandyCounter::WhenClicked()
{

}

void GUICandyCounter::WhenHovered()
{
	myTooltip.Show();
}

void GUICandyCounter::WhenLeaved()
{
	myTooltip.Close();
}

void GUICandyCounter::Render()
{
	myCandyBag->Draw(myCandyBagPosition);

	TextRenderData data;
	data.myText = myCandyCountText->myText;
	data.myPos = myCandyCountTextPosition;
	data.myColor = { 1, 1, 1, 1 };

	RenderConverter::AddRenderCommand(RenderCommand(1100.f, static_cast<unsigned short>(enumRenderLayer::eGUI), data));


	myTooltip.Render();
}

bool GUICandyCounter::RecieveMessage(const CandyAmountMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eCandyAmount)
	{
		myCandyCountText->myText = std::to_string(aMessage.myCandyAmount);
	}

	return true;
}
