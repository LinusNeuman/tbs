#pragma once
#include <StateStack/GameState.h>

class VictoryState : public GameState
{
public:
	VictoryState();
	~VictoryState();
	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;

private:
	StaticSprite * myBackgroundSprite;

};

