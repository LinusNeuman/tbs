#pragma once
#include <CU/Vectors/vector2.h>

namespace CommonUtilities
{
	Vector2f IsometricToPixel(const Vector2f & aPosition);

	Vector2f PixelToIsometric(const Vector2f & aPosition);
}