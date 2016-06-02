#pragma once
#include <Level\GameLevel.h>
#include "EnemyFactory\EnemyFactory.h"
#include "PlayerFactory\PlayerFactory.h"

struct TiledData;

class LevelFactory
{
public:
	LevelFactory();
	~LevelFactory();
	GameLevel* CreateLevel(const std::string& aLevelPath);
private:
	void LoadLevel(const std::string& aLevelPath);

	PlayerFactory myPlayerFactory;
	EnemyFactory myEnemyFactory;
	TiledData myTileData;
};