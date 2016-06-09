#include "stdafx.h"
#include "RenderCommand.h"
#include <tga2d/sprite/sprite.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

RenderCommand::RenderCommand()
{
	mySprite = nullptr;
	myText = nullptr;
}

RenderCommand::RenderCommand(DX2D::CSprite & aSpriteToRender, const CU::Vector2f & aPosition, const float aRenderPriority, const USHORT aLayer, const RenderData & aRenderData, const bool aOffsetMiddleOfScreen/* = false*/)
	: mySprite(&aSpriteToRender),
	myPosition(aPosition),
	myRenderData(aRenderData)
{
	myRenderPriority = aRenderPriority;
	myLayer = aLayer;
	myMiddleScreenOffset = aOffsetMiddleOfScreen;
	myText = nullptr;
}

USHORT RenderCommand::GetLayer()
{
	return myLayer;
}

float RenderCommand::GetPriority()
{
	return myRenderPriority;
}

RenderCommand::RenderCommand(DX2D::CText & aTextToRender, const float aRenderPriority, const USHORT aLayer, const bool aOffsetMiddleOfScreen/* = false*/)
	: myText(&aTextToRender),
	myPosition({ aTextToRender.myPosition.x, aTextToRender.myPosition.y })
{
	myRenderPriority = aRenderPriority;
	myLayer = aLayer;
	myMiddleScreenOffset = aOffsetMiddleOfScreen;
	mySprite = nullptr;
}

RenderCommand::~RenderCommand()
{
}

void RenderCommand::Render() const
{
	
	DX2D::CColor tempColor(myRenderData.myColor.r, myRenderData.myColor.g, myRenderData.myColor.b, myRenderData.myColor.a);

	DX2D::Vector2f tempPosition;

	float normalizedWindowSizeX = mySprite->GetImageSize().x / FLOATCAST(SingletonDataHolder::GetTargetResolution().x) * (16.f / 9.f);
	float normalizedWindowSizeY = mySprite->GetImageSize().y / FLOATCAST(SingletonDataHolder::GetTargetResolution().y);

	//DX2D::Vector2f tempSize(normalizedWindowSizeX * myRenderData.mySize.x, normalizedWindowSizeY * myRenderData.mySize.y);
	DX2D::Vector2f tempSize(myRenderData.mySize.x, myRenderData.mySize.y);

	if (myMiddleScreenOffset == true)
	{
		tempPosition.x = myPosition.x + 0.5f;
		tempPosition.y = myPosition.y + 0.5f;
	}
	else
	{
		tempPosition.x = myPosition.x;
		tempPosition.y = myPosition.y;
	}

	if (mySprite != nullptr)
	{
		mySprite->SetColor(tempColor);
		mySprite->SetPosition(tempPosition);
		mySprite->SetSize(tempSize);

		mySprite->SetCustomShader(myRenderData.myShaderPtr);

		mySprite->Render();

		mySprite->SetCustomShader(nullptr);
	}
	else if (myText != nullptr)
	{
		myText->myColor = tempColor;
		myText->myPosition = tempPosition;

		myText->Render();
	}
}