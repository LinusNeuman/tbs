#include "stdafx.h"
#include "Renderer.h"

#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/drawers/line_drawer.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/text/text.h>

#include "WrappedSprite.h"

Renderer::Renderer()
{
	myCommandsToRender = new CU::GrowingArray<RenderCommand>();
	myBuffer = new CU::GrowingArray<RenderCommand>();

	myCommandsToRender->Init(100);
	myBuffer->Init(100);
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
	if (WrappedSprite::ourSprites.IsInitialized() == false)
	{
		WrappedSprite::ourSprites.Init(100);
	}
}

void Renderer::Draw() const
{
	RenderAllSprites();
}


void Renderer::AddRenderCommand(RenderCommand & aRenderCommand)
{
	aRenderCommand.myPosition.x /= static_cast<float>(myWindowSize.x);
	aRenderCommand.myPosition.y /= static_cast<float>(myWindowSize.y);
	myBuffer->Add(aRenderCommand);
}

void Renderer::SwapBuffer()
{
	myCommandsToRender->RemoveAll();
	std::swap(myCommandsToRender, myBuffer);
}

void Renderer::RenderAllSprites() const
{
	myCommandsToRender->CallFunctionOnAllMembers(std::mem_fn(&RenderCommand::Render));
}