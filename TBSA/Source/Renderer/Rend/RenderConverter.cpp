#include "stdafx.h"
#include "RenderConverter.h"
#include <tga2d/sprite/sprite.h>
#include "WrappedSprite.h"
#include <CU/Vectors/vector2.h>

const float TileWidth = 10;
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

	if (WrappedSprite::myRenderConverter == nullptr)
	{
		WrappedSprite::myRenderConverter = this;
	}
}


void RenderConverter::CalculateAndRenderIso(const WrappedSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	CU::Vector2f tempPosition = aPosition;

	CU::Vector2f tempOffset(550.f, 250.f);

	CU::Vector2f newPos = CU::Vector2f((tempPosition.x - tempPosition.y) * TileSizeHalf, ((tempPosition.x + tempPosition.y) * TileSizeHalf) / 2.f);

	const float Priority = (tempPosition.x + (tempPosition.y * TileWidth));

	myRenderer.AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), tempOffset + newPos, Priority, aSpriteToRender.GetLayer()));
}

void RenderConverter::CalculateAndRenderSprite(const WrappedSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	myRenderer.AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), aPosition, 10000.f, aSpriteToRender.GetLayer()));
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
