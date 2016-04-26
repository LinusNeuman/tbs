#pragma once

namespace DX2D
{
	class CSprite;
}

class WrappedSprite
{
public:
	WrappedSprite();
	~WrappedSprite();

	void Init();

	void SetPosition(const CU::Vector2f & aPosition);
	CU::Vector2f GetPosition();

	void SetColor(const CU::Vector4f& aColor);
	void Draw();

	DX2D::CSprite * GetSprite();

private:
	DX2D::CSprite * mySprite;
	CU::Vector2f myPosition;
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