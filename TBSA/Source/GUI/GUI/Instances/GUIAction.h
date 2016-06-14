#pragma once
#include <Audio/Instances/SoundEffect.h>
#include "GUIButton.h"

class GUIAction : public GUIButton
{
public:
	GUIAction();
	virtual ~GUIAction();

	virtual void Create(const std::string& aSpritePath, CU::Vector2f aPosition, int aCost1, int aCost2);

	virtual void Update(const CU::Time &aDelta) override;

	virtual void WhenClicked() override;
	virtual void WhenHovered() override;

	virtual void Render() override;

	bool RecieveMessage(const CurrentPlayerAP & aMessage) override;

	void SetCanDo(bool aCan)
	{
		myCanDo = aCan;
	}
protected:
	int myPlayerAP;

	int myCostP1;
	int myCostP2;

	StaticSprite* myLocked;
	StaticSprite* myUnlockedGlow;

	bool myIsLocked;

	GUIAnimateState myAnimateGlowState;

	float myAnimateGlowTimer;

	void AnimateGlow(const CommonUtilities::Time aTime);
	void FadeUpGlow(const CommonUtilities::Time aTime);
	void FadeDownGlow(const CommonUtilities::Time aTime);

	void ResetAnimateGlow();

	bool myCanDo;
};
