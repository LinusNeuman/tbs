#pragma once
#pragma once

//#define CU CommonUtilities
#define Vec2f CommonUtilities::Vector2f
#define MAX_TEXT_ROWS 100
#define TEXT_HEIGHT 28
#define DEBUG_TEXTBOX

#include "../CommonUtilities/CU/NameSpaceAliases.h"
#include <string>
//#include <tga2d\text\text.h>
#include <CU\Vectors\vector2.h>
#include <CU\GrowingArray\GrowingArray.h>
#include "FalloffStack.h"

namespace DX2D
{
	class CText;
}

enum class eLinewrappingMode
{
	Word,
	Char
};

class TextBox
{
	public:
		TextBox(const Vec2f aPosition, const Vec2f aDimensions, const std::string aFontPath, eLinewrappingMode aMode = eLinewrappingMode::Char);
		~TextBox();
		void AddText(std::string aText);
		void Render() const;
		void ScrollUp();
		void ScrollDown();
		void SetLineWrappingMode(const eLinewrappingMode aMode);
		void SetSize(const Vec2f aDimensions);
		void SetPosition(const Vec2f aPosition);
		void Clear();
		void Update();

	private:
		void AddText_CharWrap(DX2D::CText* aText);
		void AddText_WordWrap(DX2D::CText* aText);

		unsigned int myCurrentLine;
		unsigned int myNumberOfLinesDisplayed;

		eLinewrappingMode myMode;

		std::string myFontPath;

		FalloffStack<DX2D::CText*, MAX_TEXT_ROWS> myTextRows;

		CU::GrowingArray<DX2D::CText*> myRenderList;

		Vec2f myPosition;
		Vec2f myDimensions;
};