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
	GameLevel* CreateLevel(const std::string& aLevelPath, CheckpointData &aCheckpointData);
private:
	void LoadLevel(const std::string& aLevelPath, CheckpointData &aCheckpointData);
	static void StaticLoad(const std::string& aFilePath, TiledData* aTilePointer, CheckpointData &aCheckpointData);

	PlayerFactory myPlayerFactory;
	EnemyFactory myEnemyFactory;
	TiledData* myTileData;

	std::thread* myThread;
	volatile bool doneLoading;
};