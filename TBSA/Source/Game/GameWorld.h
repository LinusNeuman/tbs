#pragma once
#include <GameState.h>
#include <CU/GrowingArray/GrowingArray.h>
#include "Room/IsometricTile.h"
#include <PlayerFactory/PlayerFactory.h>


class WrappedSprite;
class RenderConverter;
class Actor;
class PlayerController;

class CGameWorld : public GameState
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	virtual eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	virtual void Draw() const override;

private:
	CU::GrowingArray<IsometricTile> myTiles;

	WrappedSprite * testSprite;

	Actor *myPlayer, *myPlayer2, *myEnemy;
	PlayerController *myPlayerController;
	PlayerFactory myFactory;
};
