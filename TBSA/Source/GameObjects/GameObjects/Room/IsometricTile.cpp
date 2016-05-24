#include "stdafx.h"
#include "IsometricTile.h"
#include <Rend/StaticSprite.h>


IsometricTile::IsometricTile()
{
	myPosition = CommonUtilities::Vector2f::Zero;
	myGraphicsLayers.Init(1);
}


IsometricTile::IsometricTile(const CommonUtilities::Vector2f & aPosition)
{
	myPosition = aPosition;
	myGraphicsLayers.Init(1);
}

IsometricTile::~IsometricTile()
{
}

void IsometricTile::Init()
{
}

void IsometricTile::Draw() const
{
	for (USHORT i = 0; i < myGraphicsLayers.Size(); i++)
	{
		myGraphicsLayers[i]->Draw(myPosition );
	}
}

void IsometricTile::AddSpriteLayer(StaticSprite * aSprite)
{
	myGraphicsLayers.Add(aSprite);
}

void IsometricTile::SetDoor(const Door& aDoor)
{
	myDoor = aDoor;
}
