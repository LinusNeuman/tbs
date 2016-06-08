#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include "Door.h"
//#include "../PathFinding/NavGraph/Graph/NavGraph.h"
#include "../PathFinding/NavGraph/NavHandle.h"
#include <ActorEnums.h>

class StaticSprite;

enum class eTileType
{
	EMPTY,
	OPEN,
	BLOCKED,
	DOOR,
	DOOR_2,
	IS_OBJECTIVE,
	Size
};

enum class eTileState
{
	NONE,
	IS_WALKABLE,
	IN_RANGE,
	IN_PATH,
	UNDER_MOUSE,
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
	inline eTileState GetTileState() const;
	bool CheckIfWalkable() const;
	void ToggleDebugMode();

	void SetVisible(bool aIsVisible);
	void SetInEnemyFoV(bool aIsInFoV);
	bool GetVisible() const;
	bool GetInEnemyFov() const;
	void RemoveAvailableDirection(eDirection aDirection);
	const CU::GrowingArray<eDirection>& GetAvailableDirections() const
	{
		return myAvailableDirections;
	}

private:
	CommonUtilities::Vector2f myPosition;
	CU::GrowingArray<eDirection> myAvailableDirections;
	eTileType myType;
	unsigned int myRoomId;
	CommonUtilities::Vector2ui myIndex;
	Door myDoor;
	VertexHandle myNavVertex;

	eTileState myState;
	bool myIsVisible;
	bool myIsInEnemyFoV;

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
inline eTileState IsometricTile::GetTileState() const
{
	return myState;
}

inline bool IsometricTile::CheckIfWalkable() const
{
	return myType == eTileType::OPEN || myType == eTileType::DOOR || myType == eTileType::DOOR_2 || myType == eTileType::IS_OBJECTIVE;
}



inline void IsometricTile::ToggleDebugMode()
{
	myDebugMode =  !myDebugMode;
}

typedef CU::GrowingArray<IsometricTile> TileArray;
