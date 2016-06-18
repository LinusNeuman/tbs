#pragma once
#include <Level/GameLevel.h>
#include "EnemyFactory/EnemyFactory.h"
#include "PlayerFactory/PlayerFactory.h"
#include <thread>


struct TiledData;

class LevelFactory
{
public:
	LevelFactory();
	~LevelFactory();
	GameLevel* CreateLevel(const std::string& aLevelPath, const CU::Vector2ui aRespawnPosition, const CommonUtilities::GrowingArray<SavedDeadEnemy> &aDeadEnemyData);
private:
	void LoadLevel(const std::string& aLevelPath, const CU::Vector2ui aRespawnPosition, const CommonUtilities::GrowingArray<SavedDeadEnemy> &aDeadEnemyData);
	static void StaticLoad(const std::string& aFilePath, TiledData* aTilePointer, const CU::Vector2ui aRespawnPosition, const CommonUtilities::GrowingArray<SavedDeadEnemy> &aDeadEnemyData);

	PlayerFactory myPlayerFactory;
	EnemyFactory myEnemyFactory;
	TiledData* myTileData;

	std::thread* myThread;
	volatile bool doneLoading;
};