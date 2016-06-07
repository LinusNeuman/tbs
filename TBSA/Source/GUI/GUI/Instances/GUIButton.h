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

	void Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aAnimated, bool aPlayClickSound, bool aPlayHoverSound, bool aIsIsometric = false, bool aIsEnabled = true);

	void Update(const CU::Time &aDelta) override;

	void Render() override;

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
