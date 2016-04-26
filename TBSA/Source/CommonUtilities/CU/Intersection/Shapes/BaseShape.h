#pragma once
#include "../../Vectors/Vector.h"
#include "../../NameSpaceAliases.h"

namespace Intersection3D
{

	class BaseShape
	{
	public:
		BaseShape();
		virtual ~BaseShape();


		CU::Vector3f myPosition;

	};

};