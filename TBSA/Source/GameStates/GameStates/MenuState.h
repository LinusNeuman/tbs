#pragma once
#include <StateStack/GameState.h>

class StaticSprite;
class RenderConverter;

class MenuState : public GameState
{
public:
	MenuState();
	~MenuState();
	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;
private:
	StaticSprite * myBackgroundSprite;
};

