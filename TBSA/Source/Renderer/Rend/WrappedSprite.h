#pragma once

#include <CU/Vectors/vector2.h>

namespace DX2D
{
	class CSprite;
}

class RenderCommand;
class RenderConverter;

class WrappedSprite
{
public:
	WrappedSprite();
	~WrappedSprite();

	void Init(const std::string & aFilePath = "Sprites/trashTestFiles/biggerTestTile.png");

	void SetPosition(const CU::Vector2f & aPosition);
	CU::Vector2f GetPosition() const;

	void Draw();

	unsigned short GetLayer() const
	{
		return myLayer;
	}

	DX2D::CSprite * GetSprite() const;

	unsigned short AddImage(const std::string & aFilePath);
	
	static CU::GrowingArray<DX2D::CSprite*> ourSprites;

	unsigned short GetImageIndex()
	{
		return myImageIndex;
	}

	unsigned short myLayer;

	static RenderConverter * myRenderConverter;
private:
	

	CU::Vector2f myPosition;

	

	unsigned short myImageIndex;
};

inline void WrappedSprite::SetPosition(const CU::Vector2f & aPosition)
{
	myPosition = aPosition;
}

inline CU::Vector2f WrappedSprite::GetPosition() const
{
	return myPosition;
}

inline DX2D::CSprite * WrappedSprite::GetSprite() const
{
	return ourSprites[myImageIndex];
}