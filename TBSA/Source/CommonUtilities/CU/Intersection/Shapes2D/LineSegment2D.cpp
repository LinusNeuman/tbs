#include "stdafx.h"
#include "LineSegment2D.h"


namespace Intersection2D
{


	LineSegment2D::LineSegment2D()
	{
	}


	void LineSegment2D::ChangePosition(const CU::Vector2f aPosition)
	{
		CU::Vector2f temp = myEndPos - myStartPos;
		myStartPos = aPosition;
		myEndPos = myStartPos + temp;
	}

	void LineSegment2D::ChangePosition(const CU::Vector2f aStartPosition, const CU::Vector2f aEndPosition)
	{
		myStartPos = aStartPosition;
		myEndPos = aEndPosition;
	}

	LineSegment2D::~LineSegment2D()
	{
	}

	bool LineSegment2D::IsInside(const CU::Vector2f &aPoint) const
	{
		if ((aPoint - myStartPos).Dot(GetNormal()) <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	CU::Vector2f LineSegment2D::GetNormal() const
	{
		CU::Vector2f direction = myEndPos - myStartPos;
		return CU::Vector2f(-direction.y, direction.x).Normalize();
	}

};