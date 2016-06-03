#pragma once
#pragma once

#define CU CommonUtilities
#define Vec2f CommonUtilities::Vector2f
#define MAX_TEXT_ROWS 100
#define TEXT_HEIGHT 28
#define DEBUG_TEXTBOX

#include <string>
#include <tga2d\text\text.h>
#include <CU\Vectors\vector2.h>
#include <CU\GrowingArray\GrowingArray.h>
#include "FalloffStack.h"

enum class eLinewrappingMode
{
	Word,
	Char
};

class TextBox
{
	public:
		TextBox(const std::string aFontPath, eLinewrappingMode aMode = eLinewrappingMode::Char);

		void AddText(std::string aText);
		void Render() const;
		void ScrollUp();
		void ScrollDown();

	private:
		void Update();
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

