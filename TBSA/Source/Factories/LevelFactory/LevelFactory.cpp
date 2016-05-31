#include "stdafx.h"
#include "LevelFactory.h"
#include <TiledLoader\TiledLoader.h>

LevelFactory::LevelFactory()
{
	myTileData = nullptr;
}

LevelFactory::~LevelFactory()
{
	//delete(myTileData);
}

GameLevel* LevelFactory::CreateLevel(const std::string& aLevelPath)
{
	LoadLevel(aLevelPath);
	GameLevel* level = new GameLevel();
	level->Init(*myTileData);
}

void LevelFactory::LoadLevel(const std::string& aLevelPath)
{
	myTileData = new TiledData();
	myPlayerFactory.LoadFromJson();
	myEnemyFactory.LoadFromJson();

	myTileData->myPlayerFactory = &myPlayerFactory;
	myTileData->myEnemyFactory = &myEnemyFactory;

	TiledLoader::Load(aLevelPath, *myTileData);
}