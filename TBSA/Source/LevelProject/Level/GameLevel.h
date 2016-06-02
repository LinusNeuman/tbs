#pragma once

#include <CU/GrowingArray/GrowingArray.h>
#include <Animation/Animation.h>
#include <NavGraph\Graph\NavGraph.h>
#include <TiledData/TiledData.h>
#include <PostMaster/MessageReceiver.h>
#include <CU/Camera/Camera2D.h>
#include <GameObjects/Room/GameFloor.h>
#include <TurnManager/TurnManager.h>
#include <Message/ActorPositionChangedMessage.h>

class StaticSprite;
class RenderConverter;
class Actor;
class PlayerController;

class GameLevel : public MessageReciever
{
public:
	GameLevel();
	~GameLevel();
	void Init(TiledData* aTileData);
	void Update(const CU::Time & aTimeDelta);
	void Draw() const;

	void RecieveMessage(const DijkstraMessage & aMessage) override;
	void RecieveMessage(const NavigationClearMessage & aMessage) override;
	void ConstructNavGraph();
private:

	GameFloor myFloor;
	Player * myPlayer, *myPlayer2;
	CommonUtilities::GrowingArray<Enemy*> myEnemies;
	CommonUtilities::GrowingArray<Objective*> myObjectives;
	PlayerController *myPlayerController;
	EnemyController *myEnemyController;

	NavGraph myNavGraph;
	TiledData* myTiledData;
	CommonUtilities::Vector2ui myDimensions;

	TurnManager myTurnManager;
};