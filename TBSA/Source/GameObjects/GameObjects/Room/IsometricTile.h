#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include "Door.h"
//#include "../PathFinding/NavGraph/Graph/NavGraph.h"
#include "../PathFinding/NavGraph/NavHandle.h"
#include <ActorEnums.h>
#include <CU/StaticArray/StaticArray.h>

class StaticSprite;
class Enemy;

namespace DX2D
{
	class CCustomShader;
}

enum class eTileType
{
	EMPTY,
	OPEN,
	BLOCKED,
	DOOR,
	DOOR_2,
	IS_OBJECTIVE,
	COVER,
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

	void SetShader(DX2D::CCustomShader * aCustomShader);

	void AddSpriteLayer(StaticSprite* aSprite);
	inline eTileType GetTileType()const;
	inline void SetTileType(eTileType);

	inline int GetRoomId() const;
	inline void SetRoomId(unsigned int aId);
	inline CU::Vector2f GetPosition() const;

	void SetDoor(const Door& aDoor);
	void SetObjectiveSprites(const CommonUtilities::StaticArray<StaticSprite*, 2> someSprites);
	CommonUtilities::GrowingArray<StaticSprite *> myGraphicsLayers;
	void SetVertexHandle(VertexHandle aHandle);
	VertexHandle GetVertexHandle() const;
	void SetTileState(eTileState aState);
	inline eTileState GetTileState() const;
	bool CheckIfWalkable() const;
	void ToggleDebugMode();

	bool CheckHasCandy() const;
	void SetHasCandy();
	void TakeCandy();

	void SetVisible(bool aIsVisible);
	void SetInEnemyFoV(bool aIsInFoV, const Enemy* aEnemy);
	void SetDiscovered(bool aIsDiscovered);
	bool GetVisible() const;
	bool GetDiscovered() const;
	bool GetInEnemyFov() const;
	const Enemy* GetSeenEnemy() const;
	void RemoveAvailableDirection(eDirection aDirection);
	const CU::GrowingArray<eDirection>& GetAvailableDirections() const
	{
		return myAvailableDirections;
	}

	void SetCurrentObjectiveSprite(const unsigned short aUS)
	{
		myCurrentObjectiveSprite = aUS;
	}

	CommonUtilities::StaticArray<StaticSprite *, 2> & GetObjectiveSprite()
	{
		return myObjectiveSprites;
	}
private:
	CommonUtilities::StaticArray<StaticSprite *, 2> myObjectiveSprites;
	unsigned short myCurrentObjectiveSprite;
	unsigned int myRoomId;

	CommonUtilities::Vector2f myPosition;
	CU::GrowingArray<eDirection> myAvailableDirections;
	eTileType myType;
	
	CommonUtilities::Vector2ui myIndex;
	Door myDoor;
	VertexHandle myNavVertex;
	const Enemy *myEnemy;
	eTileState myState;

	bool myHasCandy;
	bool myIsVisible;
	bool myIsInEnemyFoV;
	bool myIsDiscovered;

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

inline bool IsometricTile::CheckHasCandy() const
{
	return myHasCandy;
}

inline void IsometricTile::SetHasCandy()
{
	myHasCandy = true;
}

inline void IsometricTile::TakeCandy()
{
	myHasCandy = false;
	myType = eTileType::OPEN;
}

typedef CU::GrowingArray<IsometricTile> TileArray;
