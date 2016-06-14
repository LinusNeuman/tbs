#pragma once

#include <StateStack/GameState.h>
#include "../TextBox/TextBox.h"

class PreGameState : public GameState, public MessageReciever
{
public:
	PreGameState();
	~PreGameState();
	void Draw() const override;
	eStackReturnValue Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack) override;

private:
	TextBox myTextBox;
};
