#include "stdafx.h"
#include "AABB2D.h"
#include "../../Macros/Macros.h"

namespace Intersection2D
{

	AABB2D::AABB2D()
	{
		myMainPoint = CU::Vector2f::Zero;
		myExtents = CU::Vector2f::Half;
		myMinPos = -CU::Vector2f::Half;
		myMaxPos = CU::Vector2f::Half;;
	}

	AABB2D::AABB2D(const CU::Vector2f aCenterPosition, CU::Vector2f aExtents)
	{
		SetPositionAndSize(aCenterPosition, aExtents);
	}

	void AABB2D::ChangePosition(const CU::Vector2f aPosition)
	{
		myMainPoint = aPosition;
		CalculateMinMax();
	}

	CU::Vector2f AABB2D::GetClosestPoint(const CU::Vector2f & aPointToCompareTo) const
	{
		CU::Vector2f temp;
		temp.x = MAX(myMinPos.x, MIN(myMaxPos.x, aPointToCompareTo.x));
		temp.y = MAX(myMinPos.y, MIN(myMaxPos.y, aPointToCompareTo.y));

		return temp;
	}

	AABB2D::~AABB2D()
	{
	}

}