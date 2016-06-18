#pragma once

#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/vector4.h>

namespace DX2D
{
	class CCustomShader;
}

struct TextRenderData
{
	CU::Vector4f myColor = CU::Vector4f::One;
	CU::Vector2f myPos;
	std::string myText;
};

struct RenderData
{
	RenderData():myColor(CU::Vector4f::One)
	{
		myShaderPtr = nullptr;
		mySize = CU::Vector2f::One;
	}

	CU::Vector2f mySizeInPixels;
	CU::Vector4f myColor;
	DX2D::CCustomShader * myShaderPtr;
	CU::Vector2f mySize;
};