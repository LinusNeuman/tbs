#include "stdafx.h"
#include "BaseShape2D.h"


BaseShape2D::BaseShape2D()
{
}


BaseShape2D::~BaseShape2D()
{
}

void BaseShape2D::ChangePosition(const CU::Vector2f aPosition)
{
	myMainPoint = aPosition;
}
