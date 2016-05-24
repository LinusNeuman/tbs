#include "stdafx.h"
#include "Fov90Frustum.h"
#include "CU/Macros/Macros.h"
#include <math.h>

namespace Intersection3D
{


	Fov90Frustum::Fov90Frustum(float aNearPlaneDistance, float aFarPlaneDistance)
	{
		myNearPlaneDistance = aNearPlaneDistance;
		myFarPlaneDistance = aFarPlaneDistance;

		float rotate45 = static_cast<float>(sin(DEGRESS_TO_RADIANSF(45)));
		//float nearX = static_cast<float>((tan(DEGRESS_TO_RADIANSF(45) / aNearPlaneDistance)));
		//float nearY = static_cast<float>((tan(DEGRESS_TO_RADIANSF(45) / aNearPlaneDistance)));

		//float farX = static_cast<float>((tan(DEGRESS_TO_RADIANSF(45) / aFarPlaneDistance)));
		//loat farY = static_cast<float>((tan(DEGRESS_TO_RADIANSF(45) / aFarPlaneDistance)));


		myNearPlane	= Plane<float>(CU::Vector3f(0.f, 0.f, aNearPlaneDistance), CU::Vector3f(0.f, 0.f, -1.f));
		myRightPlane = Plane<float>(CU::Vector3f::Zero, CU::Vector3f(rotate45, 0.f, -rotate45));
		myTopPlane = Plane<float>(CU::Vector3f::Zero, CU::Vector3f(0.f, rotate45, -rotate45));
		myLeftPlane = Plane<float>(CU::Vector3f::Zero, CU::Vector3f(-rotate45, 0.f, -rotate45));
		myDownPlane = Plane<float>(CU::Vector3f::Zero, CU::Vector3f(0.f, -rotate45, -rotate45));
		myFarPlane = Plane<float>(CU::Vector3f(0.f, 0.f, aFarPlaneDistance), CU::Vector3f(0.f, 0.f, 1.f));
	}

};