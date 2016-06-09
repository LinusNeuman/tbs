#pragma once
#include <GUI/Generic/GUIElement.h>
class GUIActionPointsBar : public GUIElement
{
public:
	GUIActionPointsBar();
	~GUIActionPointsBar();

	void WhenHovered() override;
	void WhenClicked() override;
	void WhenLeaved() override;

	void Update(const CU::Time &aDelta) override;
	void Render() override;

	bool RecieveMessage(const PlayerAPChangedMessage &aMessage) override;
private:
	CU::GrowingArray<StaticSprite*, uchar> myAPIcons;
	CU::GrowingArray<CU::Vector2f, uchar> myAPIconsPos;

	StaticSprite* myAPFullIcon;
	StaticSprite* myAPSpentIcon;

	uchar myPlayerCurrentAP;
	uchar myPlayerMaxAP;
	uchar myPlayerPreviousAP;
	uchar myPlayerPreviusMaxAP;
	bool myShouldRenderLoseAnimation;

	int myTargetResPositionX;
	int myTargetResPositionY;
	int myTargetResInterPos;

	void CalculateAPIcons();
};