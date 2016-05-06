#include "stdafx.h"
#include "IsometricTile.h"


IsometricTile::IsometricTile()
{
	myPosition = CU::Vector2f::Zero;
}


IsometricTile::IsometricTile(const CU::Vector2f & aPosition)
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