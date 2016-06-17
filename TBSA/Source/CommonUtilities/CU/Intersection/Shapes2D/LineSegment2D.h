#pragma once
#include "BaseShape2D.h"
#include "../../NameSpaceAliases.h"

namespace Intersection2D
{


	class LineSegment2D : public BaseShape2D
	{
	public:
		LineSegment2D();
		~LineSegment2D();

		LineSegment2D(CU::Vector2f aStartPosition, CU::Vector2f aEndPosition)
		{
			myStartPos = aStartPosition;
			myEndPos = aEndPosition;
		}

		void ChangePosition(const CU::Vector2f aPosition) override;
		void ChangePosition(const CU::Vector2f aStartPosition, const CU::Vector2f aEndPosition);

		bool LineSegment2D::IsInside(const CU::Vector2f &aPoint) const;

		CU::Vector2f GetNormal() const;

		CU::Vector2f myStartPos;
		CU::Vector2f myEndPos;

	};

};