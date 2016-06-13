#pragma once
#include <StateStack/GameState.h>

class StaticSprite;
class RenderConverter;

class CreditsState : public GameState, public MessageReciever
{
public:
	CreditsState();
	~CreditsState();
	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;
private:
	StaticSprite * myCreditSprite;
	CU::Vector2f myPosition;
};

