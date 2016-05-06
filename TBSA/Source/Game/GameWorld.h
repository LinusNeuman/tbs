#pragma once
#include <GameState.h>
#include <CU/GrowingArray/GrowingArray.h>
#include "Room/IsometricTile.h"

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
	CU::GrowingArray<IsometricTile> myTiles;

	WrappedSprite * testSprite;

	Player *myPlayer;
	Player *myPlayer;
	PlayerController *myPlayerController;
};
