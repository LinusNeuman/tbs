#include "stdafx.h"
#include "WrappedSprite.h"
#include "tga2d/sprite/sprite.h"
#include "RenderCommand.h"
#include "RenderConverter.h"





CU::GrowingArray<DX2D::CSprite*> WrappedSprite::ourSprites;

//RenderCommand WrappedSprite::GetRenderCommand()
//{
//	return RenderCommand(*ourSprites[myImageIndex], myPosition);
//}

WrappedSprite::WrappedSprite()
{
	myRenderConverter = nullptr;
}


WrappedSprite::WrappedSprite(RenderConverter & aRenderConverter)
{
	myRenderConverter = &aRenderConverter;
}

WrappedSprite::~WrappedSprite()
{
}

void WrappedSprite::Init(const std::string & aFilePath/* = "Sprites/Magnus.png"*/)
{
	myImageIndex = AddImage(aFilePath);
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


//void WrappedSprite::SetColor(const CU::Vector4f& aColor)
//{
////	mySprite->SetColor(DX2D::CColor(aColor.r, aColor.g, aColor.b, aColor.a));
//}

void WrappedSprite::Draw()
{
	DL_ASSERT(myRenderConverter != nullptr, "WrappedSprites render pointer is nullptr");
	myRenderConverter->CalculateAndRenderIso(*this);
}
