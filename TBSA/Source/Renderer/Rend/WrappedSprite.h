#pragma once

#include "RenderLayerEnum.h"
#include <CU/Vectors/vector2.h>
#include "RenderData.h"
#include <unordered_map>
#include <CU/Hashing/HashUtility.h>

class IndexKey
{
public:
	friend std::hash<IndexKey>;
	IndexKey(const std::string & aPath, const CU::Vector4f & aRect) :
		myPath(aPath),
		myRect(aRect)
		{}

	bool operator == (const IndexKey & aRight) const
	{
		return (myRect == aRight.myRect) && (myPath == aRight.myPath);
	}

private:
	const std::string myPath;
	const CU::Vector4f myRect;
};

namespace std {
	template <> struct hash<IndexKey>
	{
		size_t operator()(const IndexKey & aKey) const
		{
			std::hash<std::string> myHasher;
			size_t aTempHash =  myHasher(aKey.myPath);
			CU::hash_combine(aTempHash, aKey.myRect.x);
			CU::hash_combine(aTempHash, aKey.myRect.y);
			CU::hash_combine(aTempHash, aKey.myRect.z);
			CU::hash_combine(aTempHash, aKey.myRect.w);
			return aTempHash;
		}
	};
}

typedef std::unordered_map<IndexKey, unsigned short> IndexMap;

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

	void Init(const std::string & aFilePath = "Sprites/trashTestFiles/biggerTestTile.png", bool aIsIsometric = true, const CU::Vector4f & aRect = CU::Vector4f::Zero);
	void Draw(const CU::Vector2f & aPosition);

	enumRenderLayer GetLayer() const;
	void SetLayer(const enumRenderLayer aRenderLayer);

	DX2D::CSprite * GetSprite() const;
	unsigned short GetImageIndex() const;
	unsigned short AddImage(const std::string & aFilePath, const CU::Vector4f & aRect = CU::Vector4f::One);
	
	const CU::Vector4f & GetColor() const;
	void SetColor(const CU::Vector4f & aColor);

	const bool GetIsIsometric() const;
	void SetIsIsometric(const bool aFlag);
	

private:
	static CU::GrowingArray<DX2D::CSprite*> ourSprites;
	static IndexMap ourIndexDictionary;

	bool myIsIsometricFlag;

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

inline const bool WrappedSprite::GetIsIsometric() const
{
	return myIsIsometricFlag;
}

inline void WrappedSprite::SetIsIsometric(const bool aFlag)
{
	myIsIsometricFlag = aFlag;
}