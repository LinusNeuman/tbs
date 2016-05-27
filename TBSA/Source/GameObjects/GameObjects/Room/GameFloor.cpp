#include "stdafx.h"
#include "GameFloor.h"
#include <CU/GrowingArray/GrowingArray.h>


GameFloor::GameFloor()
{
}


GameFloor::~GameFloor()
{
}

void GameFloor::Update()
{
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Update));
}

void GameFloor::Draw() const
{
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Draw));
}

void GameFloor::Init(const unsigned short aSize)
{
	myTiles.Init(aSize);
}

void GameFloor::SetTiles(const TileArray & aTileArray)
{
	myTiles = aTileArray;
}





unsigned short GameFloor::Size() const
{
	return myTiles.Size();
}


