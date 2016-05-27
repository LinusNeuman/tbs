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
	myFloor.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Update));
}

void GameFloor::Draw() const
{
	myFloor.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Draw));
}

void GameFloor::Init(const unsigned short aSize)
{
	myFloor.Init(aSize);
}

void GameFloor::SetTiles(const TileArray & aTileArray)
{
	myFloor = aTileArray;
}





unsigned short GameFloor::Size() const
{
	return myFloor.Size();
}


