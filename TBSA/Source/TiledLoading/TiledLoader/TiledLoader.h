/*
*Author:  Hampus Huledal
*Date: 2016-05-06
*/
#pragma once
#include <CU/Vectors/vector2.h>
struct SavedPlayerStruct;
struct SavedDeadEnemy;
struct TiledData;



namespace TiledLoader
{
	void Load(std::string aFilePath, TiledData* aTilePointer, const CU::Vector2ui aRespawnPosition, const SavedDeadEnemy *aDeadEnemyData);
}
