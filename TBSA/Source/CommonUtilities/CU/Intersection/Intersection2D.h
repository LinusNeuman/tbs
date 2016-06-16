#pragma once
#include "CU/NameSpaceAliases.h"
#include "Shapes2D.h"
#include <cmath>

namespace Intersection2D
{

	bool KnownPointVsLineSegment(CU::Vector2f aPoint, const LineSegment2D & aLine);
	
	bool LineVsLine(const LineSegment2D & aFirstLine, const LineSegment2D & aSecondLine, CU::Vector2f & anIntersectionPoint);
	
	bool AABBVsAABB2D(const AABB2D & aFirstCube, const AABB2D & aSecondCube);

	bool AABBvsCircle(const AABB2D & aCube, const Circle2D & aCircle);
	
	bool PointInsideAABB2D(const AABB2D & aAABB, const CU::Vector2f & aPoint);

	bool LineVsCircle(const LineSegment2D & aLine, const Circle2D & aCircle, CU::Vector2f & anIntersectionPoint);

	bool PointVsCircle(CU::Vector2f aPoint, const Circle2D aCircle);


	bool CircleVSCircle(const Circle2D & aFirstCircle, const Circle2D & aSecondCircle);

	bool LineVsSweptCircle(const LineSegment2D & aLine, LineSegment2D aSweptLine, const float aSweptRadius);

	float DistanceToLine(const LineSegment2D & aLine, const CU::Vector2f & aPositition);

	float DistanceToLine2(const LineSegment2D & aLine, const CU::Vector2f & aPositition);
}