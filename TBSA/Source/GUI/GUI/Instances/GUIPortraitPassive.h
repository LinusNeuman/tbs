#pragma once
#include <Audio/Instances/SoundEffect.h>
#include "GUIButton.h"

class GUIPortraitPassive : public GUIButton
{
public:
	GUIPortraitPassive();
	virtual ~GUIPortraitPassive();

	void Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aAnimated, bool aPlayClickSound, bool aPlayHoverSound, const char* aTooltip, CU::Vector2i aTooltipsize, float aTextOffset, bool aIsIsometric = false, bool aIsEnabled = true, float aPriority = 1000.f) override;

	void Update(const CU::Time &aDelta) override;

	void WhenHovered() override;
	void WhenLeaved() override;

	void Render() override;

	bool RecieveMessage(const PlayerIDMessage & aMessage) override;
protected:
	int myPlayerID;

	StaticSprite* myCharacter0;
	StaticSprite* myCharacter1;
};