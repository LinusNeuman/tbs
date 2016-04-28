#pragma once



struct LineData
{
	LineData() :
		myStartPosition(CU::Vector2f::Zero), myEndPosition(CU::Vector2f::Zero), myColor(CU::Vector4f::One)
	{}

	LineData(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition) :
		myStartPosition(aStartPosition), myEndPosition(aEndPosition), myColor(CU::Vector4f::One)
	{}

	LineData(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition, const CU::Vector4f & aColor) :
		myStartPosition(aStartPosition), myEndPosition(aEndPosition), myColor(aColor)
	{}

	CU::Vector2f myStartPosition;
	CU::Vector2f myEndPosition;
	CU::Vector4f myColor;
};

namespace DX2D
{
	class CSpriteBatch;
	class CSprite;
	class CText;
}

class WrappedSprite;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init(const std::string & aSpriteFilePath);

	void AddNodeToDraw(WrappedSprite & aSpriteToAdd);
	void AddLineToDraw(const LineData & aLinkToDraw);

	void UpdateSprite(WrappedSprite & aSpriteToAdd);

	void PrintText(const std::string & aText, const CU::Vector2f & aPosition);
	
	void Draw() const;

	void SetWindowSize(const CU::Vector2ui & aWindowSize);

	void ResetRender();

private:
	
	CU::Vector2ui myWindowSize;

	void RenderLines();
	void RenderLine(const LineData & aLineToDraw);

	DX2D::CSpriteBatch * myNodesToDraw;
	
	CU::GrowingArray<DX2D::CSprite*> mySpritesToDraw;
	CU::GrowingArray<LineData> myLinesToDraw;
	DX2D::CText * myTextsToPrint;
};



inline void Renderer::SetWindowSize(const CU::Vector2ui & aWindowSize)
{
	myWindowSize = aWindowSize;
}