/*
*Author:  Hampus Huledal
*Date: 2016-05-06
*/
#pragma once
#include "../../Game/Room/IsometricTile.h"



class TileMap;

namespace TiledLoader
{
	void Load(std::string aFilePath, CommonUtilities::GrowingArray<IsometricTile>& someTiles);
}
