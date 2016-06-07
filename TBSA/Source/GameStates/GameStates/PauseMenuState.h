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
private:
	StaticSprite* myBackgroundSprite;
	bool myShouldAdd;
	bool myShouldPop;
};

