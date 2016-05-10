/*
*Author:  Hampus Huledal
*Date: 2016-05-06
*/
#include <string>
#include "../../Game/Room/IsometricTile.h"
#include <CU/GrowingArray/GrowingArray.h>


class TileMap;

namespace TiledLoader
{
	inline void Load(std::string aFilePath, CommonUtilities::GrowingArray<IsometricTile> someTiles);
}
