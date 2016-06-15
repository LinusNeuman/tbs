#pragma once

#include <StateStack/GameState.h>
#include "../TextBox/TextBox.h"

class PostLevelState : public GameState, public MessageReciever
{
public:
	PostLevelState(float aPoints, float aTurns, float aEnemies);
	~PostLevelState();
	void Draw() const override;
	eStackReturnValue Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack) override;

private:
	TextBox myText;
	StaticSprite* myBg;
};