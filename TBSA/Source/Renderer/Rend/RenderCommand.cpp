#include "stdafx.h"
#include "RenderCommand.h"

//const USHORT TileWidth = 10;

RenderCommand::RenderCommand()
{
	mySprite = nullptr;
}

RenderCommand::RenderCommand(DX2D::CSprite & aSpriteToRender, const CU::Vector2f & aPosition, const float aRenderPriority, const USHORT aLayer)
	: mySprite(&aSpriteToRender),
	myPosition(aPosition)
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
	mySprite->SetPosition(tempPosition);
	mySprite->Render();
}