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

	/*void SetPosition(const CU::Vector2f & aPosition);
	CU::Vector2f GetPosition() const;*/

	void Draw(const CU::Vector2f & aPosition);

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

	//static RenderConverter * myRenderConverter;
private:
	unsigned short myImageIndex;
};

inline DX2D::CSprite * WrappedSprite::GetSprite() const
{
	return ourSprites[myImageIndex];
}
