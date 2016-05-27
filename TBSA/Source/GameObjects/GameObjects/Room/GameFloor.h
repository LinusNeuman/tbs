#pragma once

#include "GameObjects/Room/IsometricTile.h"

typedef CU::Vector2ui FloorDimensions;

class GameFloor
{
public:
	GameFloor();
	~GameFloor();

	void Update();
	void Draw() const;

	void Init(const unsigned short aSize);
	void SetTiles(const TileArray & aTileArray);

	void SetFloorDimensions(const FloorDimensions aDimensionsSize);
	const FloorDimensions & GetDimensions() const;
	unsigned short Size() const;

	void CallFunctionOnAllTiles(std::function<void(IsometricTile&)> aFunction);
	void CallFunctionOnAllTiles(std::function<void(const IsometricTile&)> aFunction) const;

	IsometricTile & GetTile(unsigned int aX, unsigned int aY);
	IsometricTile & GetTile(CommonUtilities::Vector2ui aVector2Ui);
	IsometricTile & GetTile(unsigned short aIndex);

private:
	TileArray myTiles;
	FloorDimensions myDimensions;
};

inline void GameFloor::SetFloorDimensions(const FloorDimensions aDimensionsSize)
{
	myDimensions = aDimensionsSize;
}

inline const FloorDimensions & GameFloor::GetDimensions() const
{
	return myDimensions;
}

inline IsometricTile& GameFloor::GetTile(unsigned short aIndex)
{
	return  myTiles[aIndex];
}

inline IsometricTile& GameFloor::GetTile(unsigned int aX, unsigned int aY)
{
	int index = myDimensions.x * aY + aX;
	if (index < 0)
	{
		index = 0;
	}
	else if (index >= myTiles.Size())
	{
		index = myTiles.Size() - 1;
	}
	return myTiles[index];
}

inline IsometricTile& GameFloor::GetTile(CommonUtilities::Vector2ui aVector2Ui)
{
	return  GetTile(aVector2Ui.x, aVector2Ui.y);
}

inline void GameFloor::CallFunctionOnAllTiles(std::function<void(IsometricTile&)> aFunction)
{
	myTiles.CallFunctionOnAllMembers(aFunction);
}

inline void GameFloor::CallFunctionOnAllTiles(std::function<void(const IsometricTile&)> aFunction) const
{
	myTiles.CallFunctionOnAllMembers(aFunction);
}