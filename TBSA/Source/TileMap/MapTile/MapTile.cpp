#include "stdafx.h"
#include "MapTile.h"

MapTile::MapTile(eTileType aType, unsigned aRoomId, unsigned aGraphicsId, CommonUtilities::Vector2ui a2DIndex)
{
	myType = aType;
	myRoomId = aRoomId;
	myGrphicsId = aGraphicsId;
	myIndex = a2DIndex;
}
