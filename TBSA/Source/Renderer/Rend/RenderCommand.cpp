#include "stdafx.h"
#include "RenderCommand.h"
#include <tga2d/sprite/sprite.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

RenderCommand::RenderCommand()
{
	mySprite = nullptr;
	myText = nullptr;
}

RenderCommand::RenderCommand(DX2D::CSprite & aSpriteToRender, const CU::Vector2f & aPosition, const float aRenderPriority, const USHORT aLayer, const RenderData & aRenderData)
	: mySprite(&aSpriteToRender),
	myPosition(aPosition),
	myRenderData(aRenderData)
{
	myRenderPriority = aRenderPriority;
	myLayer = aLayer;
	myText = nullptr;
}

RenderCommand::RenderCommand(const float aRenderPriority, const USHORT aLayer, const TextRenderData& aRenderData, const bool aOffsetMiddleOfScreen/* = false*/)
{
	myText = new DX2D::CText("text/calibril.ttf_sdf");
	myText->myText = aRenderData.myText;
	myRenderPriority = aRenderPriority;
	myPosition = aRenderData.myPos;
	myLayer = aLayer;
	myMiddleScreenOffset = aOffsetMiddleOfScreen;
	myTextColor = aRenderData.myColor;
	mySprite = nullptr;

}

USHORT RenderCommand::GetLayer()
{
	return myLayer;
}

float RenderCommand::GetPriority()
{
	return myRenderPriority;
}



RenderCommand::~RenderCommand()
{
}

void RenderCommand::Render() const
{
	
	DX2D::CColor tempColor(myRenderData.myColor.r, myRenderData.myColor.g, myRenderData.myColor.b, myRenderData.myColor.a);

	
	DX2D::Vector2f tempPosition = {myPosition.x, myPosition.y};


	if (mySprite != nullptr)
	{
		DL_ASSERT(myRenderData.mySizeInPixels != CU::Vector2f::Zero, "Sprite size is zero during rendering");

		float normalizedWindowSizeX = myRenderData.mySizeInPixels.x / FLOATCAST(SingletonDataHolder::GetTargetResolution().x) *SingletonDataHolder::GetTargetResolutionRatio();
		float normalizedWindowSizeY = myRenderData.mySizeInPixels.y / FLOATCAST(SingletonDataHolder::GetTargetResolution().y);

		float renderScale = FLOATCAST(SingletonDataHolder::GetTargetResolution().x) / 1920.f;

		DX2D::Vector2f tempSize(normalizedWindowSizeX * renderScale, normalizedWindowSizeY * renderScale);

		mySprite->SetColor(tempColor);
		mySprite->SetPosition(tempPosition);
		mySprite->SetSize(tempSize);

		mySprite->SetCustomShader(myRenderData.myShaderPtr);

		mySprite->Render();

		mySprite->SetCustomShader(nullptr);
	}
	else if (myText != nullptr)
	{
		tempColor = DX2D::CColor(myTextColor.r, myTextColor.g, myTextColor.b, myTextColor.a);

		myText->myColor = tempColor;
		myText->myPosition = tempPosition;

		myText->Render();
	}
}