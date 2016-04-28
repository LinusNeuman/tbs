#pragma once
#include <GameState.h>

//class Renderer;
class WrappedSprite;
class RenderConverter;


class CGameWorld : public GameState
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	virtual eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	virtual void Draw() const override;
private:

	RenderConverter * myRenderer;
	

	WrappedSprite * myTestSprite;
};