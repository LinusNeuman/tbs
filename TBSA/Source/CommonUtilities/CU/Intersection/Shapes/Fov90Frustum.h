#pragma once
#include "BaseShape.h"
#include "CU/Lines And Planes/plane.h"

namespace Intersection3D
{


	class Fov90Frustum : public BaseShape
	{
	public:
		Fov90Frustum(float myNearPlaneDistance, float myFarPlaneDistance);

		float myNearPlaneDistance;
		float myFarPlaneDistance;

		Plane<float> myNearPlane;
		Plane<float> myRightPlane;
		Plane<float> myTopPlane;
		Plane<float> myLeftPlane;
		Plane<float> myDownPlane;
		Plane<float> myFarPlane;
	};
}