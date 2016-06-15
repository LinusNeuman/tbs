#pragma once
#include <StateStack/GameState.h>
class PauseMenuState : public GameState, public MessageReciever
{
public:
	PauseMenuState();
	~PauseMenuState();
	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;

	bool RecieveMessage(const GUIMessage & aMessage) override;

	virtual bool RecieveMessage(const SetTargetResolutionMessage& aMessage) override;


private:
	StaticSprite* myBackgroundSprite;

	CU::Vector2ui myTargetResolution;

	bool myShouldAdd;
	bool myShouldPop;
	bool myShouldPopMain;
	bool myShouldOptionsMenu;
};

