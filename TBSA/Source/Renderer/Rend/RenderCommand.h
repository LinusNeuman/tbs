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
	RenderCommand(DX2D::CText & aTextToRender, const float aPriority, const unsigned short aLayer, const bool aOffsetMiddleOfScreen = false);
	~RenderCommand();

	void Render() const;
	float GetPriority();
	unsigned short GetLayer();
	CU::Vector2f myPosition;

private:

	bool myMiddleScreenOffset;
	unsigned short myLayer;
	RenderData myRenderData;
	float myRenderPriority;
	DX2D::CText* myText;
	DX2D::CSprite * mySprite;
};

