#include "stdafx.h"
#include "LevelFactory.h"
#include <TiledLoader\TiledLoader.h>
#include <TiledData/TiledData.h>

LevelFactory::LevelFactory()
{
}

LevelFactory::~LevelFactory()
{
	//delete(myTileData);
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

	TiledLoader::Load(aLevelPath, myTileData);
}