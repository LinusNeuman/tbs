#include "stdafx.h"

#include "text/text_service.h"
#include "texture/texture_manager.h"
#include "text/textfile.h"
#include "text/fontfile.h"
#include "sprite/sprite_batch.h"
#include "sprite/sprite.h"
#include "sprite/textured_quad_batch.h"
#include "engine.h"

#include <iostream>
#include <fstream>

#define MAX_SPRITES 10000
#define TEXT_ENGINE_TRAVERSE_X 0.6f
#define TEXT_ENGINE_TRAVERSE_Y 0.15f

using namespace DX2D;

CTextService::CTextService()
{
	minS = 0;
	minT = 0;
	maxS =0;
	maxT = 0;
	myCurrentSprite = 0;
	myIsLoaded = false;
	myTextsToDraw = 0;

}


CTextService::~CTextService()
{
	mySprites.clear();

	for (int i = 0; i < myTextsToRender.TotalCount(); i++)
	{
		delete myTextsToRender.myData[i];
	}

}

void CTextService::Init()
{
	for (int i = 0; i< MAX_SPRITES; i++)
	{
		mySprites.push_back(new DX2D::CSprite());
	}

	myTextsToRender.Init(128);

	for (int i = 0; i < 128; i++)
	{
		SText* text = new SText();
		myTextsToRender.myData[i] = text;
	}
}

inline bool FileExists(const std::string& name) 
{
	std::ifstream f(name.c_str());
	if (f.good()) {
		f.close();
		return true;
	}
	else {
		f.close();
		return false;
	}
}

void CTextService::InitAndLoad(std::string aFontPathAndName)
{
	std::map<std::string, SFontData*>::iterator iter = myFontDatas.find(aFontPathAndName);
	if (iter != myFontDatas.end())
	{
		return;
	}

	std::string name = aFontPathAndName;

	std::string image = name;
	image.append(".dds");

	if (!FileExists(image))
	{
		ERROR_AUTO_PRINT("%s %s", "Text load error! File not found: ", image.c_str());
		return;
	}

	std::string fontFile = name;
	fontFile.append(".txt");

	if (!FileExists(fontFile))
	{
		ERROR_AUTO_PRINT("%s %s", "Text load error! File not found: ", fontFile.c_str());
		return;
	}

	SFontData* fontData = new SFontData();

	fontData->myBatch = new CSpriteBatch(false);
	fontData->myBatch->Init(image.c_str());
	fontData->myBatch->myQuadBatch->myIsScreenSpace = true;
	fontData->myBatch->SetEffect(SEffect_SignedDistanceField);
	fontData->myTexture = CEngine::GetInstance()->GetTextureManager().GetTexture(image.c_str());

	ParseFontFile(fontData->myFontChars, fontFile, static_cast<unsigned int>(fontData->myTexture->myImageSize.x), static_cast<unsigned int>(fontData->myTexture->myImageSize.y));

	myFontDatas[aFontPathAndName] = fontData;
	myIsLoaded = true;
}

void CTextService::Update()
{
	if (!myIsLoaded)
	{
		return;
	}
	for (std::map<std::string, SFontData*>::iterator iterator = myFontDatas.begin(); iterator != myFontDatas.end(); iterator++)
	{
		if (iterator->second)
		{
			iterator->second->myBatch->ClearAll();
		}
	}
	myCurrentSprite = 0;
}

float DX2D::CTextService::GetSentenceWidth(const std::string& aText, float aSize, const std::string& aName)
{
	if (aText.size() <= 0)
	{
		return 0.0f;
	}
	SFontData* fontData = myFontDatas[aName];
	if (!fontData || !myIsLoaded)
	{
		return 0;
	}
	float nextX = 0.0f;
	for (unsigned int i = 0; i < aText.size(); i++)
	{
		int aChar = aText[i];
		aChar = aChar < 0 ? 63 : aChar;
		const fontChar& theChar = fontData->myFontChars[aChar];
		nextX += (((((theChar.xadvance_ - theChar.xoffset_) / (float)CEngine::GetInstance()->GetTargetSize().x))) * aSize) * TEXT_ENGINE_TRAVERSE_X;
	}

	return nextX;

}


void CTextService::UpdateTextAndDraw(const std::string& aText, const Vector2f& aPosition, CColor aColor, float aSize, const std::string& aName)
{
	if (!myIsLoaded)
	{
		return;
	}
	
	SFontData* fontData = myFontDatas[aName];
	if (!fontData)
	{
		return;
	}


	fontData->myBufferedObjects.ResetCount();

	BuildText(aText, aPosition, aColor, aSize, aName, fontData->myBufferedObjects);
	fontData->myBatch->ClearAll();


	for (int i = 0; i < fontData->myBufferedObjects.NextCount()+1; i++)
	{
		if (i > FONT_BUFF_SIZE)
		{
			break;
		}
		STextToRender* text = fontData->myBufferedObjects.GetAt(i);
		if (myCurrentSprite < MAX_SPRITES)
		{
			DX2D::CSprite* sprite = mySprites[myCurrentSprite];
			sprite->SetPosition(text->myPosition);
			sprite->SetSize(text->mySize);
			sprite->SetColor(text->myColor);
			sprite->SetUVOffset(text->myUV);
			sprite->SetUVScale(text->uvScale);
			fontData->myBatch->AddObject(sprite);
			myCurrentSprite++;
		}
	}

	//fontData->myTextBuffer.clear();


	fontData->myBatch->Render();
//	Render();

}


void CTextService::BuildText(const std::string& aText, const Vector2f& aPosition, CColor aColor, float aSize, const std::string& aName, SSimplePointerArray<STextToRender*>& aTextBuffer)
{
	SFontData* fontData = myFontDatas[aName];
	if (!fontData || !myIsLoaded)
	{
		return;
	}
	float nextX = 0.0f;
	float nextY = 0.0f;

	float targetSizeX = (float)CEngine::GetInstance()->GetTargetSize().x;
	for (unsigned int i = 0; i< aText.size(); i++)
	{
		int aChar = static_cast<unsigned char>(aText[i]);

		aChar = aChar < 0 ? 63 : aChar;
		const fontChar& theChar = fontData->myFontChars[aChar];
		minS = theChar.sMin_;
		maxT = theChar.tMin_;
		maxS = theChar.sMax_;
		minT = theChar.tMax_;

		bool isNewLine = (aChar == 10);
		if (isNewLine)
		{
			nextY += aSize * TEXT_ENGINE_TRAVERSE_Y;
			nextX = 0;
			continue;
		}

		float sizeX = (theChar.width_ / (float)fontData->myTexture->myImageSize.x);
		float sizeY = (theChar.height_ / (float)fontData->myTexture->myImageSize.y);


		Vector2f offset(theChar.xoffset_ / (float)fontData->myTexture->myImageSize.x, theChar.yoffset_ / (float)fontData->myTexture->myImageSize.y);
		offset /= 2.0f;

		Vector2f size;
		size.x = (sizeX * aSize);
		size.y = (sizeY)* aSize;

		STextToRender* renderText = aTextBuffer.GetNext();
		if (!renderText)
		{
			ERROR_AUTO_PRINT("%s", "Too much text is rendered, either remove the number of characters rendered per frame or increase the buffer (text_service.h->FONT_BUFF_SIZE)");
			continue;
		}
		renderText->myPosition.Set((aPosition.x + nextX), nextY + aPosition.y - (offset.y * aSize));
		renderText->mySize = size;
		renderText->myUV.Set(minS, maxT);
		renderText->uvScale.x = sizeX;
		renderText->uvScale.y = sizeY;
		renderText->myColor = aColor;

		nextX += (((((theChar.xadvance_ - theChar.xoffset_) / targetSizeX))) * aSize) * TEXT_ENGINE_TRAVERSE_X;

	//	aTextBuffer.push_back(renderText);

	}



}


void CTextService::AddTextToRender(const std::string& aText, const Vector2f& aPosition, CColor aColor, float aSize, const std::string& aName)
{
	UpdateTextAndDraw(aText, aPosition, aColor, aSize, aName);
}
