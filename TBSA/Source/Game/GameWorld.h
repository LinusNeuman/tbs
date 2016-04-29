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

	virtual void SwapBuffers();
private:

	RenderConverter * myRenderer;
	//Renderer * myRenderer;

	WrappedSprite * myTestSprite;
	WrappedSprite * myTestSprite1;
	WrappedSprite * myTestSprite2;
};