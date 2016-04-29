#include "stdafx.h"
#include "RenderCommand.h"


RenderCommand::RenderCommand()
{
	mySprite = nullptr;
}

RenderCommand::RenderCommand(DX2D::CSprite & aSpriteToRender, CU::Vector2f & aPosition) 
	: mySprite(&aSpriteToRender),
	myPosition(aPosition)
{
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