#pragma once
#include <GameState.h>
#include <CU/GrowingArray/GrowingArray.h>

class WrappedSprite;
class RenderConverter;
class Player;
class PlayerController;

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
	CU::GrowingArray<WrappedSprite*> myTiles;

	WrappedSprite * myTestSprite;
	Player *myPlayer;
	PlayerController *myPlayerController;
};