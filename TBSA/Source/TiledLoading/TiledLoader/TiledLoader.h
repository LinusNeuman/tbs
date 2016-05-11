/*
*Author:  Hampus Huledal
*Date: 2016-05-06
*/

#include "../../Game/Room/IsometricTile.h"

namespace
{
	const std::string fileEnding = ".png";
}

class TileMap;

namespace TiledLoader
{
	void Load(std::string aFilePath, CommonUtilities::GrowingArray<IsometricTile>& someTiles);
}
