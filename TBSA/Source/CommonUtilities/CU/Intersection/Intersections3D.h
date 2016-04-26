#pragma once
#include "Shapes.h"
#include <cmath>

namespace Intersection3D
{
	float DistanceToLine(const LineSegment3D & aLine, const Vector3f & aPositition)
	{
		Vector3f d = aLine.myEndPos - aLine.myStartPos;
		d.Normalize();

		Vector3f e = (aPositition - aLine.myStartPos);
		Vector3f a = (e * d.Length());

		return (e.Length2() - a.Length2());
	}

	bool CompareRadiusOfLineToDistanceOfPoint(const LineSegment3D & aLine, const Vector3f & aPositition, const float aRadius, const float myRadius = 0.f)
	{
		if ((aRadius + myRadius) > DistanceToLine(aLine, aPositition))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool PointInsideSphere(const Sphere & aSphere, const Vector3f & aPoint)
	{
		Vector3f temp;
		temp = aSphere.myCenterPosition - aPoint;

		if (temp.Length() < aSphere.myRadius)
		{
			return true;
		}
		return false;
	}

	bool PointInsideAABB(const AABB & aAABB, const Vector3f & aPoint)
	{
		if (aPoint.x > aAABB.myMinPos.x &&
			aPoint.x < aAABB.myMaxPos.x &&
			aPoint.y > aAABB.myMinPos.y &&
			aPoint.y < aAABB.myMaxPos.y &&
			aPoint.z > aAABB.myMinPos.z &&
			aPoint.z < aAABB.myMaxPos.z)
		{
			return true;
		}
		return false;
	}


	bool LineVsSphere(const LineSegment3D & aLine, const Sphere & aSphere, Vector3f & anIntersectionPoint)
	{
		Vector3f hypotenuse = aSphere.myCenterPosition - aLine.myStartPos;

		Vector3f directionOfLine = aLine.myEndPos - aLine.myStartPos;
		directionOfLine.Normalize();

		Vector3f lineToMiddle = (directionOfLine * hypotenuse.Length());
		float toRoot = (aSphere.myRadiusSquared - hypotenuse.Length2() + lineToMiddle.Length2());
		if (toRoot < 0)
		{
			return false;
		}
		float perpendicular = (sqrt(toRoot));
		float difference = lineToMiddle.Length() - perpendicular;
		anIntersectionPoint = aLine.myStartPos + (directionOfLine * difference);
		if ((difference * difference) > (aLine.myEndPos - aLine.myStartPos).Length2())
		{
			return false;
		}

		return true;
	}


	bool SweptSphereVsSphere(const LineSegment3D & aLine, float aRadius, Sphere aSphere)
	{
		//float b = DistanceToLine(aLine, aSphere.myCenterPosition);

		aSphere.myRadius += aRadius;
		aSphere.myRadiusSquared = aSphere.myRadius * aSphere.myRadius;

		return LineVsSphere(aLine, aSphere, Vector3f());
	}

	bool LineVsAABB(const LineSegment3D & aLine, const AABB & aAABB, Vector3f & anIntersectionPoint)
	{
		bool isInside = true;

		Vector3f rayDelta = aLine.myEndPos - aLine.myStartPos;
		union
		{
			float xt;
			float distanceToXPlane;
		};

		if (aLine.myStartPos.x < aAABB.myMinPos.x)
		{
			distanceToXPlane = aAABB.myMinPos.x - aLine.myStartPos.x;
			if (distanceToXPlane > rayDelta.x)
			{
				return false;
			}
			distanceToXPlane /= rayDelta.x;
			isInside = false;
		}
		else if (aLine.myStartPos.x > aAABB.myMaxPos.x)
		{
			distanceToXPlane = aAABB.myMaxPos.x - aLine.myStartPos.x;
			if (distanceToXPlane < rayDelta.x)
			{
				return false;
			}
			distanceToXPlane /= rayDelta.x;
			isInside = false;
		}
		else
		{
			distanceToXPlane = -1.f;
		}

		union
		{
			float yt;
			float distanceToYPlane;
		};

		if (aLine.myStartPos.y < aAABB.myMinPos.y)
		{
			distanceToYPlane = aAABB.myMinPos.y - aLine.myStartPos.y;
			if (distanceToYPlane > rayDelta.y)
			{
				return false;
			}
			distanceToYPlane /= rayDelta.y;
			isInside = false;
		}
		else if (aLine.myStartPos.y > aAABB.myMaxPos.y)
		{
			distanceToYPlane = aAABB.myMaxPos.y - aLine.myStartPos.y;
			if (distanceToYPlane < rayDelta.y)
			{
				return false;
			}
			distanceToYPlane /= rayDelta.y;
			isInside = false;
		}
		else
		{
			distanceToYPlane = -1.f;
		}

		union
		{
			float zt;
			float distanceToZPlane;
		};

		if (aLine.myStartPos.z < aAABB.myMinPos.z)
		{
			distanceToZPlane = aAABB.myMinPos.z - aLine.myStartPos.z;
			if (distanceToZPlane > rayDelta.z)
			{
				return false;
			}
			distanceToZPlane /= rayDelta.z;
			isInside = false;
		}
		else if (aLine.myStartPos.z > aAABB.myMaxPos.z)
		{
			distanceToZPlane = aAABB.myMaxPos.z - aLine.myStartPos.z;
			if (distanceToZPlane < rayDelta.z)
			{
				return false;
			}
			distanceToZPlane /= rayDelta.z;
			isInside = false;
		}
		else
		{
			distanceToZPlane = -1.f;
		}

		if (isInside == true)
		{
			anIntersectionPoint = aLine.myStartPos;
			return true;
		}

		int hitOnWhichSide = 0;

		union
		{
			float lengthAtIntersectionOfLine;
			float t;
		};

		lengthAtIntersectionOfLine = distanceToXPlane;
		if (distanceToYPlane > lengthAtIntersectionOfLine)
		{
			hitOnWhichSide = 1;
			lengthAtIntersectionOfLine = distanceToYPlane;
		}

		if (distanceToZPlane > lengthAtIntersectionOfLine)
		{
			hitOnWhichSide = 2;
			lengthAtIntersectionOfLine = distanceToZPlane;
		}

		float x = 0;
		float y = 0;
		float z = 0;

		switch (hitOnWhichSide)
		{
		case 0:
			//intersect with yz plane

			y = aLine.myStartPos.y + rayDelta.y * lengthAtIntersectionOfLine;
			if (y < aAABB.myMinPos.y || y > aAABB.myMaxPos.y)
			{
				return false;
			}

			z = aLine.myStartPos.z + rayDelta.z * lengthAtIntersectionOfLine;
			if (z < aAABB.myMinPos.z || z > aAABB.myMaxPos.z)
			{
				return false;
			}

			break;

		case 1:
			//intersect with xz plane

			x = aLine.myStartPos.x + rayDelta.x * lengthAtIntersectionOfLine;
			if (x < aAABB.myMinPos.x || x > aAABB.myMaxPos.x)
			{
				return false;
			}

			z = aLine.myStartPos.z + rayDelta.z * lengthAtIntersectionOfLine;
			if (z < aAABB.myMinPos.z || z > aAABB.myMaxPos.z)
			{
				return false;
			}
			break;

		case 2:
			//intersect with xy plane

			x = aLine.myStartPos.x + rayDelta.x * lengthAtIntersectionOfLine;
			if (x < aAABB.myMinPos.x || x > aAABB.myMaxPos.x)
			{
				return false;
			}

			y = aLine.myStartPos.y + rayDelta.y * lengthAtIntersectionOfLine;
			if (y < aAABB.myMinPos.y || y > aAABB.myMaxPos.y)
			{
				return false;
			}

			break;

		default:
			break;
		}

		anIntersectionPoint = (rayDelta.GetNormalized() * lengthAtIntersectionOfLine);

		return true;
	}
	
	bool SweptSphereVsAABB(const LineSegment3D & aLine, float aRadius, AABB aAABB)
	{
		Vector3f distanceToChange = Vector3f::DirectionVector45Deg * aRadius;
		aAABB.myMaxPos += distanceToChange;
		aAABB.myMinPos -= distanceToChange;

		return LineVsAABB(aLine, aAABB, Vector3f());
	}

	bool SphereVsPlane(const Sphere & aSphere, const Plane<float> & aPlane)
	{
		if (aSphere.myCenterPosition.Dot(aPlane.GetNormal()) - aPlane.GetSelfProjection() < aSphere.myRadius)
		{
			return true;
		}

		return false;
	}

	bool SphereVsFrustum(const Sphere & aSphere, const Fov90Frustum & aFrustum)
	{
		if (SphereVsPlane(aSphere, aFrustum.myDownPlane) == true &&
			SphereVsPlane(aSphere, aFrustum.myFarPlane) == true &&
			SphereVsPlane(aSphere, aFrustum.myLeftPlane) == true &&
			SphereVsPlane(aSphere, aFrustum.myNearPlane) == true &&
			SphereVsPlane(aSphere, aFrustum.myRightPlane) == true &&
			SphereVsPlane(aSphere, aFrustum.myTopPlane) == true)
		{
			return true;
		}

		return false;
	}
};