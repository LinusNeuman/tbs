#include "stdafx.h"
#include "WrappedSprite.h"
#include "tga2d/sprite/sprite.h"
//#include "RenderCommand.h"
#include "RenderConverter.h"


CU::GrowingArray<DX2D::CSprite*> WrappedSprite::ourSprites;

WrappedSprite::WrappedSprite()
{
}

WrappedSprite::~WrappedSprite()
{
}

void WrappedSprite::Init(const std::string & aFilePath/* = "Sprites/Magnus.png"*/)
{
	myImageIndex = AddImage(aFilePath);
	myLayer = enumRenderLayer::eFloor;
	myColor = CU::Vector4f::One;
}

unsigned short WrappedSprite::AddImage(const std::string & aFilePath)
{
	for (unsigned short iSprite = 0; iSprite < ourSprites.Size(); ++iSprite)
	{
		if (ourSprites[iSprite]->GetImagePath() == aFilePath)
		{
			return iSprite;
		}
	}

	ourSprites.Add(new DX2D::CSprite(aFilePath.c_str()));
	ourSprites.GetLast()->SetPivot(DX2D::Vector2f(0.f, 1.0f));
	return (ourSprites.Size() - 1);
}

void WrappedSprite::Draw(const CU::Vector2f & aPosition)
{
	RenderConverter::CalculateAndRenderIso(*this, aPosition);
}