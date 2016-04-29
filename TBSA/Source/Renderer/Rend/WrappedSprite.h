#pragma once

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
	WrappedSprite(RenderConverter & aRenderConverter);
	~WrappedSprite();

	void Init(const std::string & aFilePath = "Sprites/Magnus.png");

	void SetPosition(const CU::Vector2f & aPosition);
	CU::Vector2f GetPosition() const;

	void SetColor(const CU::Vector4f& aColor);
	void Draw();

	DX2D::CSprite * GetSprite() const;

	unsigned short AddImage(const std::string & aFilePath);

	static CU::GrowingArray<DX2D::CSprite*> ourSprites;

	RenderCommand GetRenderCommand();

	unsigned short GetImageIndex()
	{
		return myImageIndex;
	}

private:
	CU::Vector2f myPosition;

	RenderConverter * myRenderConverter;

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