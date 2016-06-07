#include "TextBox.h"
#include <iostream>
#include <stack>

#ifdef DEBUG_TEXTBOX
#include <tga2d\engine.h>
#include <tga2d\drawers\debug_drawer.h>
#endif

TextBox::TextBox(const Vec2f aPosition, const Vec2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode)
{
	myRenderList.Init(1);
	myCurrentLine = 0;
	myFontPath = aFontPath;
	myMode = aMode;
	SetSize(aDimensions);
	SetPosition(aPosition);
	Update();
}

void TextBox::AddText_WordWrap(DX2D::CText* aText)
{
		if (aText->GetWidth() > myDimensions.x)
		{
			unsigned int i;
			bool foundSpace = false;
			std::string oldLine = aText->myText;

			for (i = 0; i < aText->myText.length(); ++i)
			{
				if (aText->myText[i] == ' ')
				{
					foundSpace = true;
					aText->myText = aText->myText.substr(0, i);
					break;
				}
			}

			if (foundSpace == false)
			{
				AddText_CharWrap(aText);
			}
			else
			{
				std::string newLine(oldLine.substr(i + 1));
				AddText(newLine);
			}
		}

		myTextRows.Push(aText);
}

void TextBox::AddText_CharWrap(DX2D::CText* aText)
{
	std::stack<char> wrap;

	while (aText->GetWidth() > myDimensions.x)
	{
		wrap.push(aText->myText[aText->myText.length() - 1]);
		aText->myText.pop_back();
	}

	myTextRows.Push(aText);

	if (wrap.size() != 0)
	{
		std::string nextLine;

		while (wrap.size() > 0)
		{
			nextLine.push_back(wrap.top());
			wrap.pop();
		}

		AddText(nextLine);
	}
}

void
TextBox::AddText(std::string aText)
{
	DX2D::CText* tmp = new DX2D::CText(myFontPath.c_str());
	
	tmp->myText = aText;

	switch(myMode)
	{
		case eLinewrappingMode::Char:
			AddText_CharWrap(tmp);
			break;

		default:
			AddText_CharWrap(tmp);
			//AddText_WordWrap(tmp);
			break;
	}
}

void
TextBox::SetLineWrappingMode(const eLinewrappingMode aMode)
{
	myMode = aMode;
}

void
TextBox::SetPosition(const Vec2f aPosition)
{
	myPosition = aPosition;
}

void
TextBox::SetSize(const Vec2f aPosition)
{
	myPosition = aPosition;
	myNumberOfLinesDisplayed = 0;

	for (float i = 0.f; i < myDimensions.y; i += TEXT_HEIGHT / 1080.f)
	{
		++myNumberOfLinesDisplayed;
	}
}

void
TextBox::Render() const
{
#ifdef DEBUG_TEXTBOX
	DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine({ myPosition.x, myPosition.y }, { myPosition.x + myDimensions.x, myPosition.y }, {1.f, 0.f, 0.f, 1.f});
	DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine({ myPosition.x, myPosition.y }, {myPosition.x, myPosition.y + myDimensions.y}, {1.f, 0.f, 0.f, 1.f});
	DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine({ myPosition.x + myDimensions.x, myPosition.y }, {myPosition.x + myDimensions.x, myPosition.y + myDimensions.y}, {1.f, 0.f, 0.f, 1.f});
	DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine({ myPosition.x, myPosition.y + myDimensions.y }, {myPosition.x + myDimensions.x, myPosition.y + myDimensions.y}, {1.f, 0.f, 0.f, 1.f});
#endif

	for (unsigned int i = 0; i < myRenderList.Size(); ++i)
	{
		myRenderList[static_cast<const unsigned short>(i)]->Render();
	}
}

void
TextBox::ScrollDown()
{
	if (myCurrentLine > 0)
	{
		--myCurrentLine;
		Update();
	}
}

void
TextBox::ScrollUp()
{
	if (myCurrentLine < MAX_TEXT_ROWS - myNumberOfLinesDisplayed && myTextRows[myCurrentLine + myNumberOfLinesDisplayed] != nullptr)
	{
		++myCurrentLine;
		Update();
	}
}

void
TextBox::Update()
{
	myRenderList.RemoveAll();

	unsigned int row = 0;

	for (unsigned int i = myCurrentLine; i < myCurrentLine + myNumberOfLinesDisplayed; ++i)
	{
		if (myTextRows[i] != nullptr)
		{
			myTextRows[i]->myPosition = { myPosition.x, myPosition.y + myDimensions.y - (0.025f * row) };
			myRenderList.Add(myTextRows[i]);
		}

		++row;
	}
}