#include "stdafx.h"
#include "LevelFactory.h"
#include <TiledLoader\TiledLoader.h>
#include <TiledData/TiledData.h>

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

GameLevel* LevelFactory::CreateLevel(const std::string& aLevelPath)
{
	if (myTileData != nullptr)
	{
		SAFE_DELETE(myTileData);
	}
	myTileData = new TiledData;
	LoadLevel(aLevelPath);
	GameLevel* level = new GameLevel();
	level->Init(myTileData);
	return level;
}

void LevelFactory::LoadLevel(const std::string& aLevelPath)
{
	
	StaticSprite().Init();
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

	//myThread = new std::thread(TiledLoader::Load, aLevelPath, myTileData);

	std::thread(TiledLoader::Load, aLevelPath, myTileData).detach();
	//TiledLoader::Load(aLevelPath, myTileData);

	/*for (int i = 0; i < myTileData.myEnemies.Size(); i++)
	{
		myTileData.myEnemies[i]->Init()
	}*/
}