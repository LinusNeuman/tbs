#include "stdafx.h"
#include "WrappedSprite.h"
#include "tga2d/sprite/sprite.h"
//#include "RenderCommand.h"
#include "RenderConverter.h"


CU::GrowingArray<DX2D::CSprite*> WrappedSprite::ourSprites;
IndexMap WrappedSprite::ourIndexDictionary;

WrappedSprite::WrappedSprite()
{
}

WrappedSprite::~WrappedSprite()
{
}

void WrappedSprite::Init(const std::string & aFilePath/* = "Sprites/Magnus.png"*/, bool aIsIsometric/* = true*/, const CU::Vector4f & aRect /*= CU::Vector4f::One*/)
{
	myImageIndex = AddImage(aFilePath, aRect);
	myLayer = enumRenderLayer::eFloor;
	myColor = CU::Vector4f::One;
	myIsIsometricFlag = aIsIsometric;
}

unsigned short WrappedSprite::AddImage(const std::string & aFilePath, const CU::Vector4f & aRect /*= CU::Vector4f::One*/)
{
	IndexKey tempKey(aFilePath, aRect);

	if (ourIndexDictionary.count(tempKey) > 0)
	{
		return ourIndexDictionary[tempKey];
	}

	ourSprites.Add(new DX2D::CSprite(aFilePath.c_str()));
	DX2D::CSprite * tempSprite = ourSprites.GetLast();
	

	if (aRect != CU::Vector4f::Zero)
	{
		const float spriteWidth = static_cast<float>(tempSprite->GetImageSize().x);
		const float spriteHeight = static_cast<float>(tempSprite->GetImageSize().y);

		const float TempStartPointX = aRect.x / spriteWidth;
		const float TempStartPointY = aRect.y / spriteHeight;

		const float TempWidth = aRect.Width / spriteWidth;
		const float TempHeight = aRect.Height / spriteHeight;

		const float TempEndPointX = TempStartPointX + TempWidth;
		const float TempEndPointY = TempStartPointY + TempHeight;

		tempSprite->SetTextureRect(TempStartPointX, TempStartPointY, TempEndPointX, TempEndPointY);
		tempSprite->SetSize(DX2D::Vector2f(tempSprite->GetSize().x * TempWidth, tempSprite->GetSize().y * TempHeight));
	}
	tempSprite->SetPivot(DX2D::Vector2f(0.f, 1.0f));
	ourIndexDictionary[tempKey] = (ourSprites.Size() - 1);
	return ourIndexDictionary[tempKey];
}


void WrappedSprite::Draw(const CU::Vector2f & aPosition)
{
	if (myIsIsometricFlag == true)
	{
		RenderConverter::CalculateAndRenderIso(*this, aPosition);
	}
	else
	{
		RenderConverter::CalculateAndRenderSprite(*this, aPosition);
	}
}
