#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap() :myMapHeight(0), myMapWidth(0)
{
}

TileMap::TileMap(CommonUtilities::GrowingArray<MapTile> someTiles, unsigned aMapwidth, unsigned aMapHeight)
{
	myTiles = someTiles;
	myMapWidth = aMapwidth;
	myMapHeight = aMapHeight;
}

TileMap::~TileMap()
{
	
}

MapTile const* TileMap::GetMapTileByIndex(unsigned aXindex, unsigned aYindex)
{
	return &myTiles[aYindex + myMapWidth * aXindex];
}

MapTile const* TileMap::GetMapTileByIndex(CommonUtilities::Vector2ui aIndex)
{
	return GetMapTileByIndex(aIndex.x, aIndex.y);
}
