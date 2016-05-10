#pragma once
#include <Rend/WrappedSprite.h>
#include "Door.h"

enum class eTileType
{
	EMPTY,
	OPEN,
	BLOCKED,
	DOOR,
	DOOR_2
};

class IsometricTile
{
public:
	IsometricTile();
	IsometricTile(const CU::Vector2f & aPosition);
	~IsometricTile();

	void Init();

	void Draw() const;

	inline eTileType GetTileType()const;
	inline void SetTileType(eTileType);

	inline int GetRoomId() const;
	inline void SetRoomId(unsigned int aId);

	void AddSpriteLayer(unsigned int aSprite);

	void SetDoor(const Door& aDoor);

private:
	CU::Vector2f myPosition;
	WrappedSprite * mySprite;

	eTileType myType;
	unsigned int myRoomId;
	CommonUtilities::GrowingArray<unsigned int> myGraphicsLayers;
	CommonUtilities::Vector2ui myIndex;
	Door myDoor;
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

