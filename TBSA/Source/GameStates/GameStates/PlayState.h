#pragma once
#include <StateStack/GameState.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <PlayerFactory/PlayerFactory.h>
#include <EnemyFactory/EnemyFactory.h>
#include <Animation/Animation.h>
#include <GameObjects/Room/IsometricTile.h>
#include "../../PathFinding/NavGraph/Graph/NavGraph.h"
#include <TiledData/TiledData.h>

class StaticSprite;
class RenderConverter;
class Actor;
class PlayerController;
class PlayState : public GameState
{
public:
	PlayState();
	~PlayState();
	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;

	void ConstructNavGraph();
private:
	CU::GrowingArray<IsometricTile> myTiles;
	StaticSprite * testSprite;
	Actor *myPlayer, *myPlayer2, *myEnemy;
	PlayerController *myPlayerController;
	PlayerFactory myPlayerFactory;
	EnemyFactory myEnemyFactory;
	Animation *myAnimation;
	NavGraph myNavGraph;
	TiledData myTiledData;
};

