﻿// Author:   Hampus Huledal
// CreationDate: 13/05/2016
#pragma once
#include <GameObjects/Room/IsometricTile.h>
#include "../../Factories/PlayerFactory/PlayerFactory.h"
#include "../../Factories/EnemyFactory/EnemyFactory.h"

struct TiledData
{
	TiledData()
	{
		myTiles.Init(1);
	}

	CommonUtilities::GrowingArray<IsometricTile> myTiles;
	CommonUtilities::Point2ui myMapSize;
	PlayerFactory * myPlayerFactory;
	EnemyFactory * myEnemyFactory;
};
