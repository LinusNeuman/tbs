#include "stdafx.h"
#include "RenderConverter.h"
#include <tga2d/sprite/sprite.h>
#include "WrappedSprite.h"

RenderConverter::RenderConverter()
{
}


RenderConverter::~RenderConverter()
{
}

void RenderConverter::Init(const CU::Vector2ui & aWindowSize)
{
	myRenderer.Init();
	myRenderer.SetWindowSize(aWindowSize);
}


void RenderConverter::CalculateAndRenderSprite(const WrappedSprite & aSpriteToRender)
{
	myRenderer.AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), aSpriteToRender.GetPosition()));
}

void RenderConverter::AddRenderCommand(RenderCommand & aRenderCommand)
{
	myRenderer.AddRenderCommand(aRenderCommand);
}

void RenderConverter::Draw() const
{
	myRenderer.Draw();
}

void RenderConverter::SwapBuffers()
{
	myRenderer.SwapBuffer();
}
