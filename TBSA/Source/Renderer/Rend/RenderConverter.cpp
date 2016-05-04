#include "stdafx.h"
#include "RenderConverter.h"
#include <tga2d/sprite/sprite.h>
#include "WrappedSprite.h"

const float TileSize = 64.f;
const float TileSizeHalf = 32.f;

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


void RenderConverter::CalculateAndRenderIso(const WrappedSprite & aSpriteToRender)
{
	CU::Vector2f tempPosition = aSpriteToRender.GetPosition();

	CU::Vector2f tempOffset(350.f, 0.f);

	CU::Vector2f newPos = CU::Vector2f((tempPosition.x - tempPosition.y) * TileSizeHalf, ((tempPosition.x + tempPosition.y) * TileSizeHalf) / 2.f);

	myRenderer.AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), tempOffset + newPos));
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
