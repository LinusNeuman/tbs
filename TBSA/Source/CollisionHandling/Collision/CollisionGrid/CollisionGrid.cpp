#include "stdafx.h"
#include "CollisionGrid.h"


CollisionGrid::CollisionGrid() : myTiles(1,1)
{
}


CollisionGrid::~CollisionGrid()
{
}

void CollisionGrid::AddDweller(const CU::Vector2f & aPosition, const GridDweller & aDweller)
{
	myTiles.Access(USHORTCAST(aPosition.x), USHORTCAST(aPosition.y)).AddDweller(aDweller);
}