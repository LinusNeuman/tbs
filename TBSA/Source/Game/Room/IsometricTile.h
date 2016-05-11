#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include "Door.h"


class WrappedSprite;
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
	void AddSpriteLayer(WrappedSprite* aSprite);
	inline eTileType GetTileType()const;
	inline void SetTileType(eTileType);

	inline int GetRoomId() const;
	inline void SetRoomId(unsigned int aId);

	void SetDoor(const Door& aDoor);

private:
	CommonUtilities::Vector2f myPosition;
	WrappedSprite * mySprite;

	eTileType myType;
	unsigned int myRoomId;
	CommonUtilities::GrowingArray<WrappedSprite *> myGraphicsLayers;
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

