#include "stdafx.h"
#include "RenderConverter.h"
#include <tga2d/sprite/sprite.h>
#include "WrappedSprite.h"
#include <CU/Vectors/vector2.h>

RenderConverter * RenderConverter::ourInstance = nullptr;



const float TileWidth = 10;
const float TileSize = 64.f;
const float TileSizeHalf = 32.f;

RenderConverter::RenderConverter()
{
}


RenderConverter::~RenderConverter()
{
}



void RenderConverter::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new RenderConverter();
	}
}

void RenderConverter::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}

void RenderConverter::Init(const CU::Vector2ui & aWindowSize)
{
	GetInstance().myRenderer.Init();
	GetInstance().myRenderer.SetWindowSize(aWindowSize);

	/*if (WrappedSprite::myRenderConverter == nullptr)
	{
		WrappedSprite::myRenderConverter = this;
	}*/
}


void RenderConverter::CalculateAndRenderIso(const WrappedSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	CU::Vector2f tempPosition = aPosition;

	CU::Vector2f tempOffset(550.f, 250.f);

	CU::Vector2f newPos = CU::Vector2f((tempPosition.x - tempPosition.y) * TileSizeHalf, ((tempPosition.x + tempPosition.y) * TileSizeHalf) / 2.f);

	const float Priority = (tempPosition.x + (tempPosition.y * TileWidth));

	GetInstance().myRenderer.AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), tempOffset + newPos, Priority, aSpriteToRender.GetLayer()));
}

void RenderConverter::CalculateAndRenderSprite(const WrappedSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	GetInstance().AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), aPosition, 10000.f, aSpriteToRender.GetLayer()));
}

void RenderConverter::AddRenderCommand(RenderCommand & aRenderCommand)
{
	GetInstance().myRenderer.AddRenderCommand(aRenderCommand);
}

void RenderConverter::Draw()
{
	GetInstance().myRenderer.Draw();
}

void RenderConverter::SwapBuffers()
{
	GetInstance().myRenderer.SwapBuffer();
}
