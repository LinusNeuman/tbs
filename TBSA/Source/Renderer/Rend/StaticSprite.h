#pragma once

#include "Rend/RenderLayerEnum.h"
#include <CU/Vectors/vector2.h>
#include <CU/Vectors/vector4.h>
#include "Rend/RenderData.h"
#include <unordered_map>
#include <CU/Hashing/HashUtility.h>
#pragma warning  (push)
#pragma warning(disable : 4512)

#include <sstream>

class IndexKey
{
public:
	friend std::hash<IndexKey>;
	IndexKey() :myPath(""), myRect(CU::Vector4f::Zero)
	{
	};
	IndexKey(const std::string & aPath, const CU::Vector4f & aRect) :
		myPath(aPath),
		myRect(aRect)
		{}

	bool operator == (const IndexKey & aRight) const
	{
		if ((myRect == aRight.myRect) && (myPath == aRight.myPath))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	std::string GetPath() const
	{
		return  myPath;
	}

	CU::Vector4f GetRect() const
	{
		return myRect;
	}

private:
	std::string myPath;
	CU::Vector4f myRect;
};
#pragma warning (pop)
namespace std {
	template <> struct hash<IndexKey>
	{
		size_t operator()(const IndexKey & aKey) const
		{
			size_t aTempHash = 0;
			CU::hash_combine(aTempHash, aKey.myPath);
			CU::hash_combine(aTempHash, aKey.myRect.x);
			CU::hash_combine(aTempHash, aKey.myRect.y);
			CU::hash_combine(aTempHash, aKey.myRect.z * 10.f);
			CU::hash_combine(aTempHash, aKey.myRect.w * 100.f);
			
			return aTempHash;
		}
	};
}

typedef std::unordered_map<IndexKey, unsigned short> IndexMap;

namespace DX2D
{
	class CSprite;
	class CCustomShader;
}

class RenderCommand;
class RenderConverter;
class Renderer;

class StaticSprite
{
	friend RenderConverter;
	friend Renderer;

public:
	StaticSprite();
	~StaticSprite();

	void Init(const std::string & aFilePath = "Sprites/trashTestFiles/biggerTestTile.png", bool aIsIsometric = true, const CU::Vector4f & aRect = CU::Vector4f::Zero, const CU::Vector2f & aPivotPoint = CU::Vector2f::Zero,const bool aSync = true);
	
	void Draw(const CU::Vector2f & aPositionInPixel) const;

	enumRenderLayer GetLayer() const;
	void SetLayer(const enumRenderLayer aRenderLayer);

	DX2D::CSprite * GetSprite() const;
	unsigned short GetImageIndex() const;
	unsigned short AddImage(const std::string& aFilePath, const CU::Vector4f& aRect = CU::Vector4f::One, const CU::Vector2f& aPivotPoint = CU::Vector2f::Zero);
	unsigned short AddImageAssync(const std::string & aFilePath, const CU::Vector4f & aRect = CU::Vector4f::One);
	
	CU::Vector2f GetSize();
	CU::Vector2f GetSizeWithoutWhiteSpace();

	const CU::Vector4f & GetColor() const;
	void SetColor(const CU::Vector4f & aColor);

	const bool GetIsIsometric() const;
	void SetIsIsometric(const bool aFlag);
	
	void SetPivotWithPixels(const CU::Vector2f & aPivotOffsetInPixel);
	const CU::Vector2f & GetPivotInPixels() const;

	void SetShader(DX2D::CCustomShader * aCustomShader);

	static void Sync();

	std::string myShaderName;
private:
	const RenderData & GetRenderData() const;

	static CU::GrowingArray<DX2D::CSprite*> ourSprites;
	static CU::GrowingArray<IndexKey> ourWaitingSprites;
	static CU::GrowingArray<StaticSprite*> ourSpritesWaitingForPromise;
	
	static IndexMap ourIndexDictionary;
	static IndexMap ourPromisedIndexes;
	static unsigned int ourNumberOfPromises;

	bool myIsInitiedFlag;
	bool myIsIsometricFlag;
	unsigned short myImageIndex;

	enumRenderLayer myLayer;
	RenderData myRenderData;

	CU::Vector2f myPositionOffset;

	CU::Vector2f mySizeWithoutWhitespace;
};



inline unsigned short StaticSprite::GetImageIndex() const
{
	return myImageIndex;
}
inline DX2D::CSprite * StaticSprite::GetSprite() const
{
	return ourSprites[myImageIndex];
}


inline enumRenderLayer StaticSprite::GetLayer() const
{
	return myLayer;
}
inline void StaticSprite::SetLayer(const enumRenderLayer aRenderLayer)
{
	myLayer = aRenderLayer;
}


inline const CU::Vector4f & StaticSprite::GetColor() const
{
	return myRenderData.myColor;
	//return myColor;
}
inline void StaticSprite::SetColor(const CU::Vector4f & aColor)
{
	myRenderData = aColor;
	//myColor = aColor;
}

inline const bool StaticSprite::GetIsIsometric() const
{
	return myIsIsometricFlag;
}

inline void StaticSprite::SetIsIsometric(const bool aFlag)
{
	myIsIsometricFlag = aFlag;
}

inline const CU::Vector2f & StaticSprite::GetPivotInPixels() const
{
	return myPositionOffset;
}

inline void StaticSprite::SetShader(DX2D::CCustomShader * aCustomShader)
{
	myRenderData.myShaderPtr = aCustomShader;
}




typedef StaticSprite SSprite;
