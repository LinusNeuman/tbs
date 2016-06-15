#pragma once
#include <StateStack/GameState.h>
#include <TextBox.h>

class GameOverState : public GameState, public MessageReciever
{
public:
	GameOverState(float aPoints, float aTurns, float aEnemies);
	~GameOverState();
	void Init() override;
	eStackReturnValue Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack) override;
	void Draw() const override;
	virtual bool RecieveMessage(const GUIMessage & aMessage) override;

private:
	StaticSprite* myBackgroundSprite;
	bool myShouldExit;
	TextBox myStatsBox;
};

