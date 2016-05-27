#pragma once

#include <CU/GrowingArray/GrowingArray.h>
#include <PlayerFactory/PlayerFactory.h>
#include <EnemyFactory/EnemyFactory.h>
#include <Animation/Animation.h>
#include <NavGraph/Graph/NavGraph.h>
#include <TiledData/TiledData.h>
#include <PostMaster/MessageReceiver.h>
#include <CU/Camera/Camera2D.h>
#include <GameObjects/Room/GameFloor.h>
#include <TurnManager/TurnManager.h>

class StaticSprite;
class RenderConverter;
class Actor;
class PlayerController;

class GameLevel : public MessageReciever
{
public:
	GameLevel();
	~GameLevel();
	void Init(const std::string& aLevelPath);
	void Update(const CU::Time & aTimeDelta);
	void Draw() const;

	void RecieveMessage(const DijkstraMessage & aMessage);
	void RecieveMessage(const NavigationClearMessage & aMessage);

	void ConstructNavGraph();

private:
	void RayTrace(const CU::Vector2f &aPosition, const CU::Vector2f &anotherPosition, bool aIsPlayer);
	void CreateEnemyRayTrace(const CU::Vector2f &aPosition, int aIndex, float aAngle, float aMagnitude);
	int CalculatePoint(float aValue) const;
	void CalculateFoVBasedOnAngle(const CU::Vector2f& aPosition, const CU::Vector2f &aShouldBeEnemyDirection, float aAngleInDegrees, float aMagnitude);
	void CreatePlayerFoV(const CU::Vector2f& aPosition, float aRadius);
	void CalculateCircleRayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition);
	void ResetFoV();

	GameFloor myFloor;
	Player * myPlayer, *myPlayer2;
	CommonUtilities::GrowingArray<Enemy*> myEnemies;
	PlayerController *myPlayerController;
	EnemyController *myEnemyController;

	PlayerFactory myPlayerFactory;
	EnemyFactory myEnemyFactory;

	NavGraph myNavGraph;
	TiledData myTiledData;
	CommonUtilities::Vector2ui myDimensions;
	std::vector<CU::Vector2f> myDebugStart;
	std::vector<CU::Vector2f> myDebugEnd;

	TurnManager myTurnManager;
};