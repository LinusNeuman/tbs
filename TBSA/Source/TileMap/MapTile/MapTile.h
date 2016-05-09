// Author:   Hampus Huledal
// CreationDate: 06/05/2016
#pragma once
#include "../../CommonUtilities/CU/Vectors/Vector.h"
#include "../../CommonUtilities/CU/GrowingArray/GrowingArray.h"

enum class eTileType
{
	OPEN,
	BLOCKED,
	DOOR,
	EMPTY
};

struct MapTile
{
	MapTile();
	MapTile(eTileType aType, unsigned int aRoomId, unsigned int aGraphicsId, CommonUtilities::Vector2ui& a2DIndex);

	eTileType myType;
	unsigned int myRoomId;
	CommonUtilities::GrowingArray<unsigned int> myGraphicsLayers;
	void * myActor = nullptr;
	CommonUtilities::Vector2ui myIndex;
};
