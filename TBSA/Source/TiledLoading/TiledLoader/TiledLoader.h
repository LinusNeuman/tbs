/*
*Author:  Hampus Huledal
*Date: 2016-05-06
*/
#pragma once
#include <CU/Vectors/vector2.h>
struct CheckpointData;
struct SavedPlayerStruct;
struct SavedDeadEnemy;
struct TiledData;



namespace TiledLoader
{
	void Load(std::string aFilePath, TiledData* aTilePointer, CheckpointData &aCheckpointData);
}
