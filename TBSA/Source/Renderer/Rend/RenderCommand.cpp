#include "stdafx.h"
#include "RenderCommand.h"

//const USHORT TileWidth = 10;

RenderCommand::RenderCommand()
{
	mySprite = nullptr;
}

RenderCommand::RenderCommand(DX2D::CSprite & aSpriteToRender, const CU::Vector2f & aPosition, const float aRenderPriority, const USHORT aLayer, const RenderData & aRenderData)
	: mySprite(&aSpriteToRender),
	myPosition(aPosition),
	myRenderData(aRenderData)
{
	myRenderPriority = aRenderPriority;
	myLayer = aLayer;
}

RenderCommand::~RenderCommand()
{
}


void RenderCommand::Render() const
{
	DX2D::Vector2f tempPosition(myPosition.x, myPosition.y);
	DX2D::CColor tempColor(myRenderData.myColor.r, myRenderData.myColor.g, myRenderData.myColor.b, myRenderData.myColor.a);

	mySprite->SetColor(tempColor);
	mySprite->SetPosition(tempPosition);
	mySprite->Render();
}