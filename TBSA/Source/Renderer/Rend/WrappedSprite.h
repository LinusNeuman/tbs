#pragma once

#include "RenderLayerEnum.h"
#include <CU/Vectors/vector2.h>
#include "RenderData.h"

namespace DX2D
{
	class CSprite;
}

class RenderCommand;
class RenderConverter;
class Renderer;

class WrappedSprite
{
	friend Renderer;

public:
	WrappedSprite();
	~WrappedSprite();

	void Init(const std::string & aFilePath = "Sprites/trashTestFiles/biggerTestTile.png");
	void Draw(const CU::Vector2f & aPosition);

	enumRenderLayer GetLayer() const;
	void SetLayer(const enumRenderLayer aRenderLayer);

	DX2D::CSprite * GetSprite() const;
	unsigned short GetImageIndex() const;
	unsigned short AddImage(const std::string & aFilePath);
	
	const CU::Vector4f & GetColor() const;
	void SetColor(const CU::Vector4f & aColor);

private:
	static CU::GrowingArray<DX2D::CSprite*> ourSprites;

	enumRenderLayer myLayer;

	unsigned short myImageIndex;

	CU::Vector4f myColor;
};



inline unsigned short WrappedSprite::GetImageIndex() const
{
	return myImageIndex;
}
inline DX2D::CSprite * WrappedSprite::GetSprite() const
{
	return ourSprites[myImageIndex];
}


inline enumRenderLayer WrappedSprite::GetLayer() const
{
	return myLayer;
}
inline void WrappedSprite::SetLayer(const enumRenderLayer aRenderLayer)
{
	myLayer = aRenderLayer;
}


inline const CU::Vector4f & WrappedSprite::GetColor() const
{
	return myColor;
}
inline void WrappedSprite::SetColor(const CU::Vector4f & aColor)
{
	myColor = aColor;
}