#pragma once
#include <Rend/RenderData.h>
#include <tga2d\text\text.h>

namespace DX2D
{
	class CSprite;
	class CText;
}

class RenderCommand
{
public:
	RenderCommand();
	RenderCommand(DX2D::CSprite & aSpriteToRender, const CU::Vector2f & aPosition, const float aPriority, const unsigned short aLayer, const RenderData & aRenderData);
	RenderCommand(const float aPriority, const unsigned short aLayer, const TextRenderData& RenderData, const bool aOffsetMiddleOfScreen = false, bool aUseSmallFont = false);
	~RenderCommand();

	void Render() const;
	void Delete();

	float GetPriority();
	unsigned short GetLayer();
	CU::Vector2f myPosition;

private:

	bool myMiddleScreenOffset;
	unsigned short myLayer;
	RenderData myRenderData;

	CU::Vector4f myTextColor;
	float myRenderPriority;
	DX2D::CText* myText;
	DX2D::CSprite * mySprite;

	float myTextScalar;
};

