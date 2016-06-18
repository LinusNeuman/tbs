#pragma once
#include "GUI/Generic/GUIElement.h"
#include <Audio/Instances/SoundEffect.h>

enum class GUIAnimateState
{
	eFadingUp,
	eFadingDown
};

class GUIButton : public GUIElement
{
public:
	GUIButton();
	virtual ~GUIButton();

	virtual void Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aAnimated, bool aPlayClickSound, bool aPlayHoverSound, const char* aTooltip, CU::Vector2i aTooltipsize, float aTextOffset, bool aIsIsometric = false, bool aIsEnabled = true, float aPriority = 1000.f);

	virtual void Update(const CU::Time &aDelta) override;

	virtual void Render() override;

	void WhenHovered() override;
	void WhenClicked() override;
	void WhenLeaved() override;
protected:
	StaticSprite* mySpritePressed;
	StaticSprite* mySpriteHovered;
	StaticSprite* mySpriteUnpressed;

	SoundEffect* myHoverSound;
	SoundEffect* myClickSound;

	bool myIsAnimated;
	GUIAnimateState myAnimateState;
	float myAnimateTimer;

	void ResetAnimate();
	void Animate(const CommonUtilities::Time aTime);
	void FadeUp(const CommonUtilities::Time aTime);
	void FadeDown(const CommonUtilities::Time aTime);
};
