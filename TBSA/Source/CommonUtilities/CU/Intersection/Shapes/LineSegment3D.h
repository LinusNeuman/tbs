#pragma once
#include "BaseShape.h"

namespace Intersection3D
{


	class LineSegment3D : public BaseShape
	{
	public:
		LineSegment3D();
		~LineSegment3D();


		CU::Vector3f myStartPos;
		CU::Vector3f myEndPos;

	};

};