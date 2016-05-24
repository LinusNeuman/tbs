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

#include <Rend/RenderConverter.h>

void IsometricTile::Draw() const
{
	for (USHORT i = 0; i < myGraphicsLayers.Size(); i++)
	{
		myGraphicsLayers[i]->Draw(myPosition );
	}
}

void IsometricTile::AddSpriteLayer(StaticSprite * aSprite)
{
	aSprite->SetPivotWithPixels(CU::Vector2f(64.f, 32.f));
	myGraphicsLayers.Add(aSprite);
}

void IsometricTile::SetDoor(const Door& aDoor)
{
	myDoor = aDoor;
}

void IsometricTile::SetVertexHandle(VertexHandle aHandle)
{
	myNavVertex = aHandle;
}

VertexHandle IsometricTile::GetVertexHandle()
{
	return myNavVertex;
}
