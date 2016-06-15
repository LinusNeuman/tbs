#pragma once

#include <StateStack/GameState.h>
#include "../TextBox/TextBox.h"

class PostLevelState : public GameState, public MessageReciever
{
public:
	PostLevelState(int aPoints, int aTurns, int aEnemies);
	~PostLevelState();
	void Draw() const override;
	eStackReturnValue Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack) override;

	bool RecieveMessage(const GUIMessage& aMessage) override;

private:
	TextBox myText;
	StaticSprite* myBg;
	StaticSprite* myIcons;
	bool myIsExit;
};