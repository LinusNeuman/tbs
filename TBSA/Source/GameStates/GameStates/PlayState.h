#pragma once
#include <StateStack/GameState.h>
#include <CU/GrowingArray/GrowingArray.h>



class GameLevel;

class PlayState : public GameState
{
public:
	PlayState();
	~PlayState();
	void Init() override;
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;

private:
	GameLevel * myLevel;
};