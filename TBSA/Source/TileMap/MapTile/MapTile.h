// Author:   Hampus Huledal
// CreationDate: 06/05/2016
#pragma once
#include "../../CommonUtilities/CU/Vectors/Vector.h"

enum class eTileType
{
	OPEN,
	BLOCKED,
	DOOR,
	EMPTY
};

struct MapTile
{
	MapTile(eTileType aType, unsigned int aRoomId, unsigned int aGraphicsId, CommonUtilities::Vector2ui a2DIndex);

	eTileType myType;
	unsigned int myRoomId;
	unsigned int myGrphicsId;
	void * myActor = nullptr;
	CommonUtilities::Vector2ui myIndex;
};
