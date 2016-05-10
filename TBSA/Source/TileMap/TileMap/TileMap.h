// Author:   Hampus Huledal
// CreationDate: 06/05/2016
#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include "../MapTile/MapTile.h"


class TileMap
{
public:
	TileMap();
	TileMap(CommonUtilities::GrowingArray<MapTile> someTiles, unsigned int aMapWidth, unsigned int aMapHeight);
	~TileMap();

	MapTile const * GetMapTileByIndex(unsigned int aXindex, unsigned int aYindex);
	MapTile const * GetMapTileByIndex(CommonUtilities::Vector2ui aIndex);


private:
	CommonUtilities::GrowingArray<MapTile> myTiles;
	unsigned int myMapWidth;
	unsigned int myMapHeight;
};
