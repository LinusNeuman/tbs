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

GameLevel* LevelFactory::CreateLevel(const std::string& aLevelPath, CheckpointData &aCheckpointData)
{
	if (myTileData != nullptr)
	{
		SAFE_DELETE(myTileData);
	}
	GameLevel* level = new GameLevel();
	myTileData = new TiledData;

	

	if (aCheckpointData.myObjectiveState.GetIsInitialized() == false)
	{
		myTileData->myObjectiveManager = &level->GetObjectiveManager();
		myTileData->myObjectiveManager->Init();
		myTileData->myObjectiveManager->SetShouldLoadData(true);
	}
	else
	{
		level->GetObjectiveManager() = aCheckpointData.myObjectiveState;
		myTileData->myObjectiveManager = &level->GetObjectiveManager();
		myTileData->myObjectiveManager->AddAsReciever();
		myTileData->myObjectiveManager->SetShouldLoadData(false);
	}

	LoadLevel(aLevelPath, aCheckpointData);
	level->Init(myTileData);
	return level;
}

void LevelFactory::LoadLevel(const std::string& aLevelPath, CheckpointData &aCheckpointData)
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

	StaticLoad(aLevelPath, myTileData, aCheckpointData);
	//std::thread(StaticLoad, aLevelPath, myTileData, aCheckpointData).detach();
	//TiledLoader::Load(aLevelPath, myTileData);

	
}

void LevelFactory::StaticLoad(const std::string& aFilePath, TiledData* aTilePointer, CheckpointData &aCheckpointData)
{
	if (aTilePointer->myObjectiveManager->GetShouldLoadData() == true)
	{
		aTilePointer->myObjectiveManager->LoadFromJson(OBJECTIVE_LOCATION + aFilePath);
	}
	TiledLoader::Load(LEVEL_LOCATION + aFilePath, aTilePointer, aCheckpointData);
}