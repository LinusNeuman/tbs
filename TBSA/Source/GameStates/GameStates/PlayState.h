#pragma once
#include <StateStack/GameState.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <PlayerFactory/PlayerFactory.h>
#include <EnemyFactory/EnemyFactory.h>
#include <Animation/Animation.h>
#include <GameObjects/Room/IsometricTile.h>
#include "../../PathFinding/NavGraph/Graph/NavGraph.h"
#include <TiledData/TiledData.h>
#include <PostMaster/MessageReceiver.h>
#include <CU/Camera/Camera2D.h>

class StaticSprite;
class RenderConverter;
class Actor;
class PlayerController;
class PlayState : public GameState, public MessageReciever
{
public:
	PlayState();
	~PlayState();
	void Init() override;
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;

	void RecieveMessage(const DijkstraMessage & aMessage)override;
	void RecieveMessage(const NavigationClearMessage & aMessage)override;

	void ConstructNavGraph();

	IsometricTile & GetTile(unsigned int aX, unsigned int aY);
	IsometricTile & GetTile(CommonUtilities::Vector2ui aVector2Ui);
private:
	Camera2D myCamera;

	CU::GrowingArray<IsometricTile> myTiles;
	StaticSprite * testSprite;
	Actor *myPlayer, *myPlayer2, *myEnemy;
	PlayerController *myPlayerController;
	PlayerFactory myPlayerFactory;
	EnemyFactory myEnemyFactory;
	Animation *myAnimation;
	NavGraph myNavGraph;
	TiledData myTiledData;
	CommonUtilities::Vector2ui myDimensions;
};

inline IsometricTile& PlayState::GetTile(unsigned aX, unsigned aY)
{
	int index = myTiledData.myMapSize.x * aY + aX;
	if (index < 0)
	{
		index = 0;
	}
	else if (index >= myTiles.Size())
	{
		index = myTiles.Size() - 1;
	}
	return myTiles[index];
}

inline IsometricTile& PlayState::GetTile(CommonUtilities::Vector2ui aVector2Ui)
{
	return  GetTile(aVector2Ui.x, aVector2Ui.y);
}