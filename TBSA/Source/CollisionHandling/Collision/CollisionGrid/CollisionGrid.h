#pragma once

#include <CU/GridArray/GridArray.h>
#include <Collision/CollisionGrid/GridTile.h>

class GridDweller;

class CollisionGrid
{
public:
	CollisionGrid();
	~CollisionGrid();


	void AddDweller(const CU::Vector2f & aPosition, const GridDweller & aDweller);

private:
	CU::GridArray<GridTile> myTiles;
};