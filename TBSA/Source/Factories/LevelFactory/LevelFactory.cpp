#include "stdafx.h"
#include "LevelFactory.h"
#include <TiledLoader\TiledLoader.h>
#include <TiledData/TiledData.h>

#define OBJECTIVE_LOCATION std::string("Data/Objectives/")
#define LEVEL_LOCATION std::string("Data/Tiled/")

LevelFactory::LevelFactory()
{
	myPlayerFactory.LoadFromJson();
	myEnemyFactory.LoadFromJson();
	myThread = nullptr;
	myTileData = nullptr;
}

LevelFactory::~LevelFactory()
{
}

GameLevel* LevelFactory::CreateLevel(const std::string& aLevelPath, const CU::Vector2ui aRespawnPosition, const CommonUtilities::GrowingArray<SavedDeadEnemy> &aDeadEnemyData)
{
	if (myTileData != nullptr)
	{
		SAFE_DELETE(myTileData);
	}
	GameLevel* level = new GameLevel();
	myTileData = new TiledData;

	myTileData->myObjectiveManager = &level->GetObjectiveManager();

	LoadLevel(aLevelPath, aRespawnPosition, aDeadEnemyData);
	level->Init(myTileData);
	return level;
}

void LevelFactory::LoadLevel(const std::string& aLevelPath, const CU::Vector2ui aRespawnPosition, const CommonUtilities::GrowingArray<SavedDeadEnemy> &aDeadEnemyData)
{
	
	//StaticSprite().Init();
	myTileData->myPlayerFactory = &myPlayerFactory;
	myTileData->myEnemyFactory = &myEnemyFactory;

	if (myTileData->myPlayers[0] != nullptr && myTileData->myPlayers[1] != nullptr)
	{
		myTileData->myPlayerFactory->ReturnPlayer(myTileData->myPlayers[0]);
		myTileData->myPlayerFactory->ReturnPlayer(myTileData->myPlayers[1]);
	}

	for (int i = 0; i < myTileData->myEnemies.Size(); i++)
	{
		if (myTileData->myEnemies[i] != nullptr)
		{
			myTileData->myEnemyFactory->ReturnEnemy(myTileData->myEnemies[i]);
		}
	}

	myTileData->myEnemies.RemoveAll();
	myTileData->myTiles.RemoveAll();
	
	myTileData->myIsLoaded = false;

	std::thread(StaticLoad, aLevelPath, myTileData, aRespawnPosition, aDeadEnemyData).detach();
	//TiledLoader::Load(aLevelPath, myTileData);

	
}

void LevelFactory::StaticLoad(const std::string& aFilePath, TiledData* aTilePointer, const CU::Vector2ui aRespawnPosition, const CommonUtilities::GrowingArray<SavedDeadEnemy> &aDeadEnemyData)
{
	aTilePointer->myObjectiveManager->LoadFromJson(OBJECTIVE_LOCATION + aFilePath);
	TiledLoader::Load(LEVEL_LOCATION + aFilePath, aTilePointer, aRespawnPosition, aDeadEnemyData);
}
