#include "stdafx.h"
#include "Renderer.h"

#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/drawers/line_drawer.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/text/text.h>
#include <tga2d/drawers/debug_drawer.h>s


//#include <CU/NameSpaceAliases.h>
#include "WrappedSprite.h"
#include "RenderLayerEnum.h"
#include "RenderCommand.h"


Renderer::Renderer()
{
	myCommandsToRender = new CommonUtilities::GrowingArray<CommonUtilities::GrowingArray<RenderCommand>>();
	myBuffer = new CommonUtilities::GrowingArray<CommonUtilities::GrowingArray<RenderCommand>>();

	myCommandsToRender->Init(static_cast<USHORT>(enumRenderLayer::enumLength));

	for (USHORT iLayer = 0; iLayer < static_cast<USHORT>(enumRenderLayer::enumLength); ++iLayer)
	{
		myCommandsToRender->Add(CommonUtilities::GrowingArray<RenderCommand>());
		myCommandsToRender->GetLast().Init(128);
	}

	myBuffer->Init(static_cast<USHORT>(enumRenderLayer::enumLength));

	for (USHORT iLayer = 0; iLayer < static_cast<USHORT>(enumRenderLayer::enumLength); ++iLayer)
	{
		myBuffer->Add(CommonUtilities::GrowingArray<RenderCommand>());
		myBuffer->GetLast().Init(128);
	}
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
	
	for (USHORT iRenderCommand = 0; iRenderCommand < (*myBuffer)[aRenderCommand.GetLayer()].Size(); ++iRenderCommand)
	{
		if (aRenderCommand.GetPriority() < 
			(*myBuffer)[aRenderCommand.GetLayer()][iRenderCommand].GetPriority())
		{
			(*myBuffer)[aRenderCommand.GetLayer()].Insert(iRenderCommand, aRenderCommand);
			return;
		}
	}
	(*myBuffer)[aRenderCommand.GetLayer()].Add(aRenderCommand);
}

void Renderer::DrawLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition)
{
	/*DX2D::Vector2f tempStartPosition(aStartPosition.x / myWindowSize.x, aStartPosition.y / myWindowSize.y);
	DX2D::Vector2f tempEndPosition(aEndPosition.x / myWindowSize.x, aEndPosition.y / myWindowSize.y);

	DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(tempStartPosition , tempEndPosition);*/
}

void Renderer::SwapBuffer()
{
	myCommandsToRender->CallFunctionOnAllMembers(std::mem_fn(&CU::GrowingArray<RenderCommand>::RemoveAll));
	std::swap(myCommandsToRender, myBuffer);
}

void Renderer::RenderAllSprites() const
{
	for (USHORT iLayer = 0; iLayer < myCommandsToRender->Size(); ++iLayer)
	{
		(*myCommandsToRender)[iLayer].CallFunctionOnAllMembers(std::mem_fn(&RenderCommand::Render));
	}
}