#pragma once
#include "GUIButton.h"
#include <Message/CandyAmountMessage.h>

class GUICandyCounter : public GUIButton
{
public:
	GUICandyCounter();
	~GUICandyCounter();

	virtual void Create(const std::string& aSpritePath, CU::Vector2f aPosition, int aCost1, int aCost2, const char* aTooltip, CU::Vector2i aTooltipSize);

	virtual void Update(const CU::Time &aDelta) override;

	virtual void WhenClicked() override;
	virtual void WhenLeaved() override;
	virtual void WhenHovered() override;

	virtual void Render() override;

	virtual bool RecieveMessage(const CandyAmountMessage &aMessage) override;
private:
	StaticSprite* myCandyBag;
	CU::Vector2f myCandyBagPosition;

	DX2D::CText* myCandyCountText;
	CU::Vector2f myCandyCountTextPosition;
};