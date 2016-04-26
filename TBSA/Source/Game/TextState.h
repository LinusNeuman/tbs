#pragma once
#include <GameState.h>

class Renderer;

class TextState : public GameState
{
public:
	TextState();
	~TextState();

	virtual void Init() override;

	virtual eStackReturnValue Update(const CU::Time & aDeltaTime, ProxyStateStack & aStateStack) override;

	virtual void Draw() override;

private:
	Renderer * myRenderer;

};

