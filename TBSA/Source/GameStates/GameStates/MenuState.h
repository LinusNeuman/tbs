#pragma once
#include <StateStack/GameState.h>

class StaticSprite;
class RenderConverter;

class MenuState : public GameState, public MessageReciever
{
public:
	MenuState();
	~MenuState();
	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;

	bool RecieveMessage(const GUIMessage & aMessage) override;
private:
	StaticSprite * myBackgroundSprite;
	bool myShouldAdd;
	bool myShouldSelect;
};