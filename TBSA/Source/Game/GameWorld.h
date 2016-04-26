#pragma once
#include <GameState.h>

class Renderer;
class WrappedSprite;


class CGameWorld : public GameState
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	virtual eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	virtual void Draw() override;
private:

	Renderer * myRenderer;

	WrappedSprite * myTestSprite;
};