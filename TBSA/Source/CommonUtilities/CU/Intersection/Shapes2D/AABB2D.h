#pragma once
#include "BaseShape2D.h"
//#include "../..NameSpaceAliases.h"

namespace Intersection2D
{

	class AABB2D : public BaseShape2D
	{
	public:
		AABB2D();
		~AABB2D();

		AABB2D(const CU::Vector2f aCenterPosition, const CU::Vector2f aExtents);

		CU::Vector2f myExtents;
		CU::Vector2f myMinPos;
		CU::Vector2f myMaxPos;

		void SetPosition(const CU::Vector2f aCenterPosition)
		{
			myMainPoint = aCenterPosition;
			CalculateMinMax();
		}

		void SetSize(const float aSize)
		{
			SetSize(CU::Vector2f(aSize, aSize));
		}

		void SetSize(const CU::Vector2f aSize)
		{
			SetPositionAndSize(myMainPoint, aSize);
		}

		void SetPositionAndSize(const CU::Vector2f aCenterPosition = CU::Vector2f::Zero, const CU::Vector2f aExtents = CU::Vector2f::Half)
		{
			myExtents = aExtents;
			SetPosition(aCenterPosition);
		}

		void SetWithMaxAndMinPos(const CU::Vector2f aMinPosition, const CU::Vector2f aMaxPosition)
		{
			myMinPos = aMinPosition;
			myMaxPos = aMaxPosition;
			CalculateCenterAndExtents();
		}

		virtual void ChangePosition(const CU::Vector2f aPosition) override;

		CU::Vector2f GetClosestPoint(const CU::Vector2f & aPointToCompareTo) const;

	private:
		void CalculateMinMax()
		{
			myMinPos = myMainPoint - myExtents;
			myMaxPos = myMainPoint + myExtents;
		}

		void CalculateCenterAndExtents()
		{
			myMainPoint = myMinPos + (myMaxPos / 2);

			myExtents = myMainPoint - myMinPos;
			abs(myExtents.x);
			abs(myExtents.y);
		}

	};

}