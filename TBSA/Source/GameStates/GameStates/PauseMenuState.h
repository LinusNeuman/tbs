#pragma once
#include "C:\Users\stline1\Source\Repos\tbs\TBSA\Source\StateStack\StateStack\GameState.h"
class PauseMenuState : public GameState, public MessageReciever
{
public:
	PauseMenuState();
	~PauseMenuState();
	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;

	bool RecieveMessage(const GUIMessage & aMessage) override;
private:
	StaticSprite* myBackgroundSprite;
	bool myShouldAdd;
};

