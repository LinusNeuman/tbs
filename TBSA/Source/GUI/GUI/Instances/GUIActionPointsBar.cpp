#include "GUIActionPointsBar.h"
#include <Message/PlayerAPChangedMessage.h>

GUIActionPointsBar::GUIActionPointsBar()
{
	myPlayerMaxAP = 5;
	myPlayerCurrentAP = 0;
	myShouldRenderLoseAnimation = false;

	myTargetResPositionX = (25 / 1920);
	myTargetResPositionY = (755 / 1080);
	myTargetResInterPos = (38 / 1920);
}


GUIActionPointsBar::~GUIActionPointsBar()
{
}

void GUIActionPointsBar::Render()
{
	for (unsigned char ch = 0; ch < myPlayerMaxAP; ++ch)
	{
		myAPIcons[ch]->Draw({myAPIconsPos[ch]});
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
			myAPIconsPos.Add({ 25.f + (ch * 38.f), 755.f });
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