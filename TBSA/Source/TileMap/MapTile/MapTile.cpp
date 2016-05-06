#include "stdafx.h"
#include "MapTile.h"

MapTile::MapTile()
{
	myGraphicsLayers.Init(1);
}

MapTile::MapTile(eTileType aType, unsigned aRoomId, unsigned aGraphicsId, CommonUtilities::Vector2ui& a2DIndex)
{
	myGraphicsLayers.Init(1);
	myType = aType;
	myRoomId = aRoomId;
	myGraphicsLayers.Add(aGraphicsId);
	myIndex = a2DIndex;
}
