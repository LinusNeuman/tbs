#pragma once
#include <StateStack/GameState.h>
#include "OptionsMenuElements/Options.h"

class OptionsMenuState : public GameState, public MessageReciever
{
public:
	OptionsMenuState();
	~OptionsMenuState();
	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;

	bool RecieveMessage(const GUIMessage & aMessage) override;

private:
	StaticSprite* myBackgroundSprite;

	bool myShouldPop;

	Options myOptionsWrapped; // From point and click project 2 holy shit what a fucking code mining accident
};

