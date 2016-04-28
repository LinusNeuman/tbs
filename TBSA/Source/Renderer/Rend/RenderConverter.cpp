#include "stdafx.h"
#include "RenderConverter.h"


RenderConverter::RenderConverter()
{
}


RenderConverter::~RenderConverter()
{
}

void RenderConverter::Init(const std::string & aSpriteFilePath, const CU::Vector2ui & aWindowSize)
{
	myRenderer.Init(aSpriteFilePath);
	myRenderer.SetWindowSize(aWindowSize);
}

void RenderConverter::AddSpriteToBeDraw(WrappedSprite & aSprite)
{
	myRenderer.AddNodeToDraw(aSprite);
}

void RenderConverter::UpdateSprite(WrappedSprite & aSpriteToUpdate)
{
	myRenderer.UpdateSprite(aSpriteToUpdate);
}

void RenderConverter::CalculateAndRenderSprite(const WrappedSprite & aSpriteToRender) const
{

}

void RenderConverter::Draw() const
{
	myRenderer.Draw();
}