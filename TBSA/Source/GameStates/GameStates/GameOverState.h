#pragma once
#include <StateStack/GameState.h>

class GameOverState : public GameState
{
public:
	GameOverState();
	~GameOverState();
	void Init() override;
	eStackReturnValue Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack) override;
	void Draw() const override;
private:
	StaticSprite* myBackgroundSprite;

};

