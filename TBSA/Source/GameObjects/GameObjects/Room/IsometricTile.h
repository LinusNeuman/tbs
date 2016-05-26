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

enum class eTileState
{
	NONE,
	IS_WALKABLE,
	IN_RANGE,
	IN_PATH,
	UNDER_MOUSE,
	FIELD_OF_VIEW,
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
	void Update();

	void AddSpriteLayer(StaticSprite* aSprite);
	inline eTileType GetTileType()const;
	inline void SetTileType(eTileType);

	inline int GetRoomId() const;
	inline void SetRoomId(unsigned int aId);
	inline CU::Vector2f GetPosition() const;

	void SetDoor(const Door& aDoor);

	CommonUtilities::GrowingArray<StaticSprite *> myGraphicsLayers;
	void SetVertexHandle(VertexHandle aHandle);
	VertexHandle GetVertexHandle() const;

	void SetTileState(eTileState aState);

	bool CheckIfWalkable() const;

	void ToggleDebugMode();
private:
	CommonUtilities::Vector2f myPosition;

	eTileType myType;
	unsigned int myRoomId;
	CommonUtilities::Vector2ui myIndex;
	Door myDoor;
	VertexHandle myNavVertex;

	eTileState myState;

	bool myDebugMode;
};

inline eTileType IsometricTile::GetTileType() const
{
	return myType;
}

inline void IsometricTile::SetTileType(eTileType aType)
{
	if (aType != eTileType::EMPTY)
	{
		myType = aType;
	}
}

inline int IsometricTile::GetRoomId() const
{
	return myRoomId;
}

inline void IsometricTile::SetRoomId(unsigned int anID)
{
	myRoomId = anID;
}

inline CU::Vector2f IsometricTile::GetPosition() const
{
	return myPosition;
}
inline void IsometricTile::SetTileState(eTileState aState)
{
	myState = aState;
}

inline bool IsometricTile::CheckIfWalkable() const
{
	return myType == eTileType::OPEN || myType == eTileType::DOOR || myType == eTileType::DOOR_2;
}

inline void IsometricTile::ToggleDebugMode()
{
	myDebugMode =  !myDebugMode;
}
