#pragma once
#include "BaseShape2D.h"

namespace Intersection2D
{

	class Circle2D : public BaseShape2D
	{
	public:
		Circle2D();
		Circle2D(const CU::Vector2f aPosition, const float aRadius);
		virtual ~Circle2D();



		float RadiusSquared() const;

		float myRadius;

	};

}