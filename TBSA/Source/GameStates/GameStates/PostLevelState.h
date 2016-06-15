#pragma once

#include <StateStack/GameState.h>
#include "../TextBox/TextBox.h"

class PostLevelState : public GameState, public MessageReciever
{
public:
	PostLevelState(unsigned int aPoints, unsigned int aTurns, unsigned int aEnemies);
	~PostLevelState();
	void Draw() const override;
	eStackReturnValue Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack) override;

private:
	bool myRender;
	TextBox myText;
};

