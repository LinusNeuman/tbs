#include "stdafx.h"
#include "WrappedSprite.h"
#include "tga2d/sprite/sprite.h"





CU::GrowingArray<DX2D::CSprite*> WrappedSprite::ourSprites;

WrappedSprite::WrappedSprite()
{
}


WrappedSprite::~WrappedSprite()
{
}

void WrappedSprite::Init(const std::string & aFilePath/* = "Sprites/Magnus.png"*/)
{
	//mySprite = new DX2D::CSprite(aFilePath.c_str());

	myImageIndex = AddImage(aFilePath);

	mySprite = new DX2D::CSprite(nullptr);
	mySprite->SetPivot(DX2D::Vector2f(0.5f, 0.5f));
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
	return (ourSprites.Size() - 1);
}

unsigned short WrappedSprite::AddNewSprite(const std::string & aFilePath)
{
	
}


void WrappedSprite::SetColor(const CU::Vector4f& aColor)
{
	mySprite->SetColor(DX2D::CColor(aColor.r, aColor.g, aColor.b, aColor.a));
}

void WrappedSprite::Draw()
{

	DX2D::Vector2f tempPosition(myPosition.x, myPosition.y);
	mySprite->SetPosition(tempPosition);
}
