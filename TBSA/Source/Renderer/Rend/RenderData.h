#pragma once

#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/vector4.h>

struct RenderData
{
	RenderData():myColor(CU::Vector4f::One)
	{}
	RenderData(const CU::Vector4f & aColor) :
		myColor(aColor)
	{}
	RenderData(const RenderData& aData) : myColor(aData.myColor)
	{}

	CU::Vector4f myColor;
};