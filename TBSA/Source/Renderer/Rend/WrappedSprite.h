#pragma once

namespace DX2D
{
	class CSprite;
}

class RenderCommand;

class WrappedSprite
{
public:
	WrappedSprite();
	~WrappedSprite();

	void Init(const std::string & aFilePath = "Sprites/Magnus.png");

	void SetPosition(const CU::Vector2f & aPosition);
	CU::Vector2f GetPosition();

	void SetColor(const CU::Vector4f& aColor);
	void Draw();

	DX2D::CSprite * GetSprite();

	unsigned short AddImage(const std::string & aFilePath);

	static CU::GrowingArray<DX2D::CSprite*> ourSprites;

	RenderCommand GetRenderCommand();

	unsigned short GetImageIndex()
	{
		return myImageIndex;
	}

private:
	DX2D::CSprite * mySprite;
	CU::Vector2f myPosition;

	unsigned short myImageIndex;
};

inline void WrappedSprite::SetPosition(const CU::Vector2f & aPosition)
{
	myPosition = aPosition;
}

inline CU::Vector2f WrappedSprite::GetPosition()
{
	return myPosition;
}

inline DX2D::CSprite * WrappedSprite::GetSprite()
{
	return mySprite;
}