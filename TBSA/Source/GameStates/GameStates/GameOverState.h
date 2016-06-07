#pragma once
#include <StateStack/GameState.h>

class GameOverState : public GameState, public MessageReciever
{
public:
	GameOverState();
	~GameOverState();
	void Init() override;
	eStackReturnValue Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack) override;
	void Draw() const override;
	virtual bool RecieveMessage(const GUIMessage & aMessage) override;

private:
	StaticSprite* myBackgroundSprite;
	bool myShouldExit;

};

