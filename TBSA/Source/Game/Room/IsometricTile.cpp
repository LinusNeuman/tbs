#include "stdafx.h"
#include "IsometricTile.h"
#include <Rend/WrappedSprite.h>


IsometricTile::IsometricTile()
{
	myPosition = CommonUtilities::Vector2f::Zero;
}


IsometricTile::IsometricTile(const CommonUtilities::Vector2f & aPosition)
{
	myPosition = aPosition;
}

IsometricTile::~IsometricTile()
{
}

void IsometricTile::Init()
{
	mySprite = new WrappedSprite();
	mySprite->Init();
}

void IsometricTile::Draw() const
{
	mySprite->Draw(myPosition);
}

void IsometricTile::AddSpriteLayer(WrappedSprite * aSprite)
{
	myGraphicsLayers.Add(aSprite);
}

void IsometricTile::SetDoor(const Door& aDoor)
{
	myDoor = aDoor;
}
