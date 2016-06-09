#pragma once

#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/vector4.h>

namespace DX2D
{
	class CCustomShader;
}

struct RenderData
{
	RenderData():myColor(CU::Vector4f::One)
	{
		myShaderPtr = nullptr;
	}
	RenderData(const CU::Vector4f & aColor) :
		myColor(aColor)
	{
		myShaderPtr = nullptr;
	}
	/*RenderData(const RenderData& aData) : myColor(aData.myColor)
	{}*/

	CU::Vector2f mySize;
	CU::Vector4f myColor;
	DX2D::CCustomShader * myShaderPtr;
};