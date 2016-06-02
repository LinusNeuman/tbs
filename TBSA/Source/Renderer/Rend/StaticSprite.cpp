#include "stdafx.h"
#include "StaticSprite.h"
#include "tga2d/sprite/sprite.h"
#include "RenderConverter.h"
#include <CU/Utility/Math/Isometric.h>




CU::GrowingArray<DX2D::CSprite*> StaticSprite::ourSprites;
IndexMap StaticSprite::ourIndexDictionary;

StaticSprite::StaticSprite()
{
	myIsInitiedFlag = false;
}

StaticSprite::~StaticSprite()
{
}

void StaticSprite::Init(const std::string & aFilePath/* = "Sprites/trashTestFiles/biggerTestTile.png"*/, bool aIsIsometric/* = true*/, const CU::Vector4f & aRect /*= CU::Vector4f::Zero*/)
{
	myIsInitiedFlag = true;
	myIsIsometricFlag = aIsIsometric;
	myImageIndex = AddImage(aFilePath, aRect);
	myLayer = enumRenderLayer::eFloor;
	
}

unsigned short StaticSprite::AddImage(const std::string & aFilePath, const CU::Vector4f & aRect /*= CU::Vector4f::One*/)
{
	IndexKey tempKey(aFilePath, aRect);

	if (ourIndexDictionary.count(tempKey) > 0)
	{
		unsigned short tempIndex = ourIndexDictionary[tempKey];
		return tempIndex;
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

		mySizeWithoutWhitespace = { aRect.z, aRect.w };
	}

	if (myIsIsometricFlag == true)
	{
		tempSprite->SetPivot(DX2D::Vector2f(0.f, 1.0f));
	}
	else
	{
		tempSprite->SetPivot(DX2D::Vector2f(0.f, 0.0f));
	}

	ourIndexDictionary[tempKey] = (ourSprites.Size() - 1);
	return ourIndexDictionary[tempKey];
}

CU::Vector2f StaticSprite::GetSize()
{
	return CU::Vector2f(GetSprite()->GetSize().x, GetSprite()->GetSize().y);
}

CU::Vector2f StaticSprite::GetSizeWithoutWhiteSpace()
{
	return mySizeWithoutWhitespace;
}

/*
	Sprite will be added to buffer and rendered next frame. Changes after this point will not affect the sprite on the buffer.
*/
void StaticSprite::Draw(const CU::Vector2f & aPosition)
{
	DL_ASSERT(myIsInitiedFlag == true, "Static sprite not initialized");

	if (myIsIsometricFlag == true)
	{
		RenderConverter::CalculateAndRenderIso(*this, aPosition - myPositionOffset);
	}
	else
	{
		RenderConverter::CalculateAndRenderSprite(*this, aPosition);
	}
}


void StaticSprite::SetPivotWithPixels(const CU::Vector2f & aPivotOffsetInPixel)
{
	CU::Vector2f tempOffset = aPivotOffsetInPixel;
	tempOffset.y = -tempOffset.y;

	myPositionOffset = CU::PixelToIsometric(tempOffset);
}

const RenderData & StaticSprite::GetRenderData() const
{
	return myRenderData;
}