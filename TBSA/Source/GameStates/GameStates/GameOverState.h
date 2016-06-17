#pragma once
#include <StateStack/GameState.h>
#include <TextBox.h>
#include "Controllers/MouseController.h"

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
	MouseController myMouseController;

	StaticSprite* myBackgroundSprite;
	StaticSprite* myIcons;
	StaticSprite* myGameOverSprite;
	bool myShouldDisplayStats;
	bool myShouldExit;
	TextBox myStatsBox;
};

