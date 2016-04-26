#pragma once
#include <GameState.h>

class Renderer;
class WrappedSprite;

class InteMartinKakaState : public GameState
{
public:
	InteMartinKakaState();
	~InteMartinKakaState();

	virtual void Init() override;

	virtual eStackReturnValue Update(const CU::Time & aDeltaTime, ProxyStateStack & aStateStack) override;

	virtual void Draw() override;

private:
	Renderer * myRenderer;
	WrappedSprite * myTestSprite;

};

