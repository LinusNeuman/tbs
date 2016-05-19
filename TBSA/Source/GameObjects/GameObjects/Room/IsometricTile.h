#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include "Door.h"
//#include "../PathFinding/NavGraph/Graph/NavGraph.h"
#include "../PathFinding/NavGraph/NavHandle.h"


class StaticSprite;

enum class eTileType
{
	EMPTY,
	OPEN,
	BLOCKED,
	DOOR,
	DOOR_2,
	Size
};

class IsometricTile
{
public:
	IsometricTile();
	IsometricTile(const CommonUtilities::Vector2f & aPosition);
	~IsometricTile();

	void Init();

	void Draw() const;
	void AddSpriteLayer(StaticSprite* aSprite);
	inline eTileType GetTileType()const;
	inline void SetTileType(eTileType);

	inline int GetRoomId() const;
	inline void SetRoomId(unsigned int aId);

	void SetDoor(const Door& aDoor);

	void SetVertexHandle(VertexHandle aHandle);
	VertexHandle GetVertexHandle();
private:
	CommonUtilities::Vector2f myPosition;
	StaticSprite * mySprite;

	eTileType myType;
	unsigned int myRoomId;
	CommonUtilities::GrowingArray<StaticSprite *> myGraphicsLayers;
	CommonUtilities::Vector2ui myIndex;
	Door myDoor;
	VertexHandle myNavVertex;
};

inline eTileType IsometricTile::GetTileType() const
{
	return myType;
}

inline void IsometricTile::SetTileType(eTileType aType)
{
	myType = aType;
}

inline int IsometricTile::GetRoomId() const
{
	return myRoomId;
}

inline void IsometricTile::SetRoomId(unsigned int anID)
{
	myRoomId = anID;
}

