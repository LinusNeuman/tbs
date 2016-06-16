#include "stdafx.h"
#include "Circle2D.h"


Intersection2D::Circle2D::Circle2D()
{
}

Intersection2D::Circle2D::Circle2D(const CU::Vector2f aPosition, const float aRadius)
{
	myMainPoint = aPosition;
	myRadius = aRadius;
}

Intersection2D::Circle2D::~Circle2D()
{
}

float Intersection2D::Circle2D::RadiusSquared() const
{
	return (myRadius * myRadius);
}

