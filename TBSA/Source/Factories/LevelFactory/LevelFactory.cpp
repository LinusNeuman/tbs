#include "stdafx.h"
#include "LevelFactory.h"
#include <TiledLoader\TiledLoader.h>
#include <TiledData/TiledData.h>

LevelFactory::LevelFactory()
{
}

LevelFactory::~LevelFactory()
{
}

GameLevel* LevelFactory::CreateLevel(const std::string& aLevelPath)
{
	LoadLevel(aLevelPath);
	GameLevel* level = new GameLevel();
	level->Init(&myTileData);
	return level;
}

void LevelFactory::LoadLevel(const std::string& aLevelPath)
{
	myPlayerFactory.LoadFromJson();
	myEnemyFactory.LoadFromJson();

	myTileData.myPlayerFactory = &myPlayerFactory;
	myTileData.myEnemyFactory = &myEnemyFactory;

	myTileData.myEnemies.RemoveAll();

	TiledLoader::Load(aLevelPath, myTileData);

	/*for (int i = 0; i < myTileData.myEnemies.Size(); i++)
	{
		myTileData.myEnemies[i]->Init()
	}*/
}