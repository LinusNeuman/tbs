#include "GUIActionPointsBar.h"
#include <Message/PlayerAPChangedMessage.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

GUIActionPointsBar::GUIActionPointsBar()
{
	myPlayerMaxAP = 6;
	myPlayerCurrentAP = 6;
	myShouldRenderLoseAnimation = false;

	myTargetResPositionX = (25.f / 1920.f) * SingletonDataHolder::GetTargetResolution().x;
	myTargetResPositionY = (755.f / 1080.f) * SingletonDataHolder::GetTargetResolution().y;
	myTargetResInterPos = (39.f / 1920.f) * SingletonDataHolder::GetTargetResolution().x;

	myAPSpentIcon = new StaticSprite();
	myAPSpentIcon->Init("Sprites/GUI/HUD/AP/Spent.dds", false, {0.f,0.f, 36.f, 46.f});
	myAPSpentIcon->SetLayer(enumRenderLayer::eGUI);

	myAPFullIcon = new StaticSprite();
	myAPFullIcon->Init("Sprites/GUI/HUD/AP/Full.dds", false, { 0.f, 0.f, 36.f, 46.f });
	myAPFullIcon->SetLayer(enumRenderLayer::eGUI);

	myAPIcons.Init(6);
	myAPIconsPos.Init(6);

	CalculateAPIcons();

	SingletonPostMaster::AddReciever(RecieverTypes::ePlayerAPChanged, *this);
}


GUIActionPointsBar::~GUIActionPointsBar()
{
	SAFE_DELETE(myAPSpentIcon);
	SAFE_DELETE(myAPFullIcon);
	myAPIcons.DeleteAll();

	SingletonPostMaster::RemoveReciever(*this);
}

void GUIActionPointsBar::WhenHovered()
{
}

void GUIActionPointsBar::WhenClicked()
{
}

void GUIActionPointsBar::WhenLeaved()
{
}

void GUIActionPointsBar::Update(const CU::Time& aDelta)
{
}

void GUIActionPointsBar::Render()
{
	for (unsigned char ch = 0; ch < myPlayerMaxAP; ++ch)
	{
		myAPIcons[ch]->Draw(myAPIconsPos[ch]);
	}
}

bool GUIActionPointsBar::RecieveMessage(const PlayerAPChangedMessage& aMessage)
{
	myPlayerCurrentAP = aMessage.myAP;

	CalculateAPIcons();

	return true;
}

void GUIActionPointsBar::CalculateAPIcons()
{
	for (unsigned char ch = 0; ch < myPlayerMaxAP; ++ch)
	{
		if (ch >= myAPIcons.Size())
		{
			myAPIcons.Add(myAPSpentIcon);
			myAPIconsPos.Add({ myTargetResPositionX + (ch * myTargetResInterPos), myTargetResPositionY });
		}
	}

	for (unsigned char ch = 0; ch < myPlayerMaxAP; ++ch)
	{
		if (ch < myPlayerCurrentAP)
		{
			myAPIcons[ch] = myAPFullIcon;
		}
		else // If this icon is not filled
		{
			if (ch < myPlayerPreviousAP) // If previously was full - play lose animation
			{
				myAPIcons[ch] = myAPSpentIcon;
				//myLoseHPAnimation.SetPosition(myParentPosition + myHPIconsPos[ch]);
				//myLoseHPAnimation.Reset(eDirectionNone);
				myShouldRenderLoseAnimation = true;
			}
		}
	}

	myPlayerPreviousAP = myPlayerCurrentAP;
	myPlayerPreviusMaxAP = myPlayerMaxAP;
}