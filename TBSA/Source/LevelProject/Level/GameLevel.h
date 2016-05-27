#pragma once
#include <StateStack/GameState.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <PlayerFactory/PlayerFactory.h>
#include <EnemyFactory/EnemyFactory.h>
#include <Animation/Animation.h>
#include <GameObjects/Room/IsometricTile.h>
#include <NavGraph/Graph/NavGraph.h>
#include <TiledData/TiledData.h>
#include <PostMaster/MessageReceiver.h>
#include <CU/Camera/Camera2D.h>
#include <TurnManager/TurnManager.h>
#include <GameObjects/Room/GameFloor.h>


class RenderConverter;
class Actor;
class PlayerController;

class GameLevel : public MessageReciever
{
public:
	GameLevel();
	~GameLevel();

	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack);
	void Draw() const;

	void RecieveMessage(const DijkstraMessage & aMessage)override;
	void RecieveMessage(const NavigationClearMessage & aMessage)override;

	void ConstructNavGraph();

private:
	void RayTrace(const CU::Vector2f &aPosition, const CU::Vector2f &anotherPosition);
	void CalculateRayTrace(int aIndex, float aAngle, float aMagnitude);
	int CalculatePoint(float aValue) const;
	void CalculateFoVBasedOnAngle(const CU::Vector2f &aShouldBeEnemyDirection, float aAngleInDegrees, float aMagnitude);
	void CalculateCircleFoV(const CU::Vector2f& aPosition, float aRadius);
	void CalculateCircleRayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition);

	GameFloor myFloor;
	Actor *myPlayer, *myPlayer2, *myEnemy;
	PlayerController *myPlayerController;
	PlayerFactory myPlayerFactory;
	EnemyFactory myEnemyFactory;

	NavGraph myNavGraph;
	TiledData myTiledData;
	CommonUtilities::Vector2ui myDimensions;
	std::vector<CU::Vector2f> myDebugStart;
	std::vector<CU::Vector2f> myDebugEnd;

	TurnManager myTurnManager;
};

