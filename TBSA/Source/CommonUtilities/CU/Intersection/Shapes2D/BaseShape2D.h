#pragma once
#include "../../Vectors/vector2.h"
#include "../../NameSpaceAliases.h"

class BaseShape2D
{
public:
	BaseShape2D();
	virtual ~BaseShape2D();

	virtual void ChangePosition(const CU::Vector2f aPosition);

	CU::Vector2f myMainPoint;
};