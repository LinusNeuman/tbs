#include "stdafx.h"
#include "RenderCommand.h"

//const USHORT TileWidth = 10;

RenderCommand::RenderCommand()
{
	mySprite = nullptr;
}

RenderCommand::RenderCommand(DX2D::CSprite & aSpriteToRender, CU::Vector2f & aPosition, const float aRenderPriority) 
	: mySprite(&aSpriteToRender),
	myPosition(aPosition)
{
	myRenderPriority = aRenderPriority;
	//myRenderPriority = (aPosition.x + (aPosition.y * TileWidth));
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