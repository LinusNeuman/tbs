#pragma once
#include "Shapes.h"
#include <cmath>

namespace Intersection
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

		/*Vector3f minPos = aAABB.myMinPos;
		Vector3f maxPos = aAABB.myMaxPos;

		Vector3f minPosWithMaxY = aAABB.myMinPos;
		minPosWithMaxY.y = aAABB.myMaxPos.y;

		Vector3f minPosWithMaxZ = aAABB.myMinPos;
		minPosWithMaxZ.z = aAABB.myMaxPos.z;

		Vector3f minPosWithMaxX = aAABB.myMinPos;
		minPosWithMaxX.x = aAABB.myMaxPos.x;

		Vector3f maxPosWithMinY = aAABB.myMaxPos;
		maxPosWithMinY.y = aAABB.myMinPos.y;

		Vector3f maxPosWithMinX = aAABB.myMaxPos;
		maxPosWithMinX.x = aAABB.myMinPos.x;

		Vector3f maxPosWithMinZ = aAABB.myMaxPos;
		maxPosWithMinZ.z = aAABB.myMinPos.z;

		if (CompareRadiusOfLineToDistanceOfPoint(aLine, minPos, aRadius) ||
			CompareRadiusOfLineToDistanceOfPoint(aLine, maxPos, aRadius) ||

			CompareRadiusOfLineToDistanceOfPoint(aLine, minPosWithMaxX, aRadius) ||
			CompareRadiusOfLineToDistanceOfPoint(aLine, minPosWithMaxY, aRadius) ||
			CompareRadiusOfLineToDistanceOfPoint(aLine, minPosWithMaxZ, aRadius) ||

			CompareRadiusOfLineToDistanceOfPoint(aLine, maxPosWithMinX, aRadius) ||
			CompareRadiusOfLineToDistanceOfPoint(aLine, maxPosWithMinY, aRadius) ||
			CompareRadiusOfLineToDistanceOfPoint(aLine, maxPosWithMinZ, aRadius))
		{
			return true;
		}
		else
		{
			return false;
		}*/

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
	
	bool KnownPointVsLineSegment(Vector2f aPoint, const LineSegment2D & aLine)
	{
		const float LineLength = (aLine.myEndPos - aLine.myStartPos).Length2();
	
		const float pointLength1 = (aPoint - aLine.myStartPos).Length2();
		const float pointLength2 = (aPoint - aLine.myEndPos).Length2();

		if (pointLength1 > LineLength ||
			pointLength2 > LineLength)
		{
			return false;
		}

		return true;
	}

	//bool LineVsLine(const LineSegment2D & aFirstLine, const LineSegment2D & aSecondLine, Vector3f & anIntersectionPoint)
	//{
	//	const Vector2f TheD = Vector2f(aFirstLine.myStartPos.x + aSecondLine.myStartPos.y, aFirstLine.myEndPos.x + aSecondLine.myEndPos.y);

	//	Vector2f a = aFirstLine.myStartPos;
	//	Vector2f b = aFirstLine.myEndPos;
	//	Vector2f c = aSecondLine.myStartPos;
	//	Vector2f d = aSecondLine.myEndPos;


	//	float numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
	//	float numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

	//	float numerator1 = ((aSecondLine.myEndPos.y * TheD.x) - (aSecondLine.myStartPos * TheD.y));
	//	//float numerator2 = ((aFirstLine.myStartPos * TheD.y) - (aFirstLine.myEndPos * TheD.x)).Length();

	//	//float denominator = ((aFirstLine.myEndPos.x - aFirstLine.myStartPos.x) * ( aSecondLine.myEndPos.y - aSecondLine.myStartPos.y)) - ((aFirstLine.myEndPos.y - aFirstLine.myStartPos.y) * (aSecondLine.myEndPos.x - aSecondLine.myStartPos.x));
	//	float denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));

	//	if (denominator == 0)
	//	{
	//		if (numerator1 == 0 &&
	//			numerator2 == 0)
	//		{
	//			return true;
	//			// fix later anIntersectionPoint ;				
	//		}
	//		else
	//		{
	//			return false;
	//			// fix later anIntersectionPoint ;
	//		}
	//	}

	//	
	//	

	//	Vector2f tempPos;

	//	tempPos.x = numerator1 / denominator;
	//	tempPos.y = numerator2 / denominator;
	//	
	//	if (KnownPointVsLineSegment(tempPos, aFirstLine) == false ||
	//		KnownPointVsLineSegment(tempPos, aSecondLine) == false)
	//	{
	//		return false; 
	//	}
	//	
	//	anIntersectionPoint.x = tempPos.x;
	//	anIntersectionPoint.y = tempPos.y;
	//	anIntersectionPoint.z = 0.f;

	//	return true;
	//}

	bool LineVsLine(const LineSegment2D & aFirstLine, const LineSegment2D & aSecondLine, Vector3f & anIntersectionPoint)
	{
		const Vector2f Line1 = aFirstLine.myEndPos - aFirstLine.myStartPos;
		const Vector2f Line2 = aSecondLine.myEndPos - aSecondLine.myStartPos;

		const Vector2f Line1Normal = Vector2f(-Line1.y, Line1.x).Normalize();
		
		const Vector2f Line2Normal = Vector2f(-Line2.y, Line2.x).Normalize();
		
		const float Line1DistanceFromZero = Vector2f::Dot(Line1Normal, aFirstLine.myStartPos);
		const float Line2DistanceFromZero = Vector2f::Dot(Line2Normal, aSecondLine.myStartPos);

		const float numeratorX = (Line2Normal.y * Line1DistanceFromZero) - (Line1Normal.y * Line2DistanceFromZero);
		const float numeratorY = (Line1Normal.x * Line2DistanceFromZero) - (Line2Normal.x * Line1DistanceFromZero);

		const float denominator = (Line1Normal.x * Line2Normal.y) - (Line2Normal.x * Line1Normal.y);

		if (denominator == 0)
		{
			if (numeratorX == 0 && numeratorY == 0)
			{
				const float Line1Length = Line1.Length();
				const float Line2Length = Line2.Length();

				const Vector2f Line1Normalized = Line1.GetNormalized();
				const Vector2f Line2Normalized = Line2.GetNormalized();
				

				
				if (Line1Normalized.Dot(aSecondLine.myEndPos - aFirstLine.myStartPos) < Line1Length &&
					Line1Normalized.Dot(aSecondLine.myEndPos - aFirstLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aSecondLine.myEndPos;
					return true;
				}



				if (Line1Normalized.Dot(aSecondLine.myStartPos - aFirstLine.myStartPos) < Line1Length &&
					Line1Normalized.Dot(aSecondLine.myStartPos - aFirstLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aSecondLine.myStartPos;
					return true;
				}


				if (Line1Normalized.Dot(aFirstLine.myEndPos - aSecondLine.myStartPos) < Line2Length &&
					Line1Normalized.Dot(aFirstLine.myEndPos - aSecondLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aFirstLine.myEndPos;
					return true;
				}


				if (Line1Normalized.Dot(aFirstLine.myStartPos - aSecondLine.myStartPos) < Line2Length &&
					Line1Normalized.Dot(aFirstLine.myStartPos - aSecondLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aFirstLine.myStartPos;
					return true;
				}
				
				return false;

			}

			return false;
		}

		Vector2f tempPoint;

		tempPoint.x = numeratorX / denominator;
		tempPoint.y = numeratorY / denominator;

		if (KnownPointVsLineSegment(tempPoint, aFirstLine) == false ||
			KnownPointVsLineSegment(tempPoint, aSecondLine) == false)
		{
			return false;
		}

		anIntersectionPoint.x = tempPoint.x;
		anIntersectionPoint.y = tempPoint.y;

		return true;
	}
};