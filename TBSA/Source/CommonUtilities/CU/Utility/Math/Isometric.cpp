#include "stdafx.h"
#include "Isometric.h"

const float TileWidth = 10;
const float TileSize = 128.f;
const float TileSizeHalf = 64.f;

namespace CommonUtilities
{
	CU::Vector2f CommonUtilities::IsometricToPixel(const CU::Vector2f & aPosition)
	{
		CU::Vector2f returnPosition;

		returnPosition.x = (aPosition.x - aPosition.y) * TileSizeHalf;
		returnPosition.y = (aPosition.x + aPosition.y) * TileSizeHalf / 2.f;

		return returnPosition;
	}

	Vector2f PixelToIsometric(const Vector2f & aPosition)
	{
		CU::Vector2f returnPosition;

		returnPosition.x = (aPosition.x / TileSizeHalf + (aPosition.y / (TileSizeHalf / 2.f))) / 2.f;
		returnPosition.y = (aPosition.y / (TileSizeHalf / 2.f) - (aPosition.x / TileSizeHalf)) / 2.f;

		return returnPosition;
	}
}