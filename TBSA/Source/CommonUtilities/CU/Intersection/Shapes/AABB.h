#pragma once
#include "BaseShape.h"

namespace Intersection3D
{

	class AABB : public BaseShape
	{
	public:
		AABB();
		~AABB();


		CU::Vector3f myCenterPos;
		CU::Vector3f myExtents;
		CU::Vector3f myMinPos;
		CU::Vector3f myMaxPos;


	};

};