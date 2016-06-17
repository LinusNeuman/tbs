﻿// Author:   Hampus Huledal
// CreationDate: 13/05/2016
#pragma once
#include <GameObjects/Room/IsometricTile.h>
#include "../../Factories/PlayerFactory/PlayerFactory.h"
#include "../../Factories/EnemyFactory/EnemyFactory.h"
#include "../../Factories/ObjectiveFactory/ObjectiveFactory.h"

#include <CU/StaticArray/StaticArray.h>
#include <atomic>
#include "../../LevelProject/ObjectivesManager/ObjectiveManager.h"
#include "../../GameObjects/Checkpoint.h"

struct TiledData
{
	TiledData()
	{
		myTiles.Init(1);
		myEnemies.Init(1);
		myIsLoaded = false;
		myPlayers[0] = nullptr;
		myPlayers[1] = nullptr;
		myObjectives.Init(1);
		myCheckpoints.Init(1);
	}

	CommonUtilities::GrowingArray<IsometricTile> myTiles;
	CommonUtilities::Point2ui myMapSize;
	PlayerFactory * myPlayerFactory;
	EnemyFactory * myEnemyFactory;
	ObjectiveFactory* myObjectiveFactory;
	ObjectiveManager* myObjectiveManager;
	CommonUtilities::StaticArray<Player*, 2> myPlayers;
	CommonUtilities::GrowingArray<Enemy*> myEnemies;
	CommonUtilities::GrowingArray<Objective*> myObjectives;
	CommonUtilities::GrowingArray<Checkpoint*> myCheckpoints;

	std::atomic<bool> myIsLoaded;
};
