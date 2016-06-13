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

	CU::Vector2f mySizeInPixels;
	CU::Vector4f myColor;
	DX2D::CCustomShader * myShaderPtr;
};