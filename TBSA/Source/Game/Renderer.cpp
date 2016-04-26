#include "stdafx.h"
#include "Renderer.h"

#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/drawers/line_drawer.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/text/text.h>

#include "WrappedSprite.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init(const std::string & aSpriteFilePath)
{
	myNodesToDraw = new DX2D::CSpriteBatch(true);
	//myNodesToDraw->Init(aSpriteFilePath.c_str());
	myNodesToDraw->Init("Sprites/palm.dds");
	myTextsToPrint = new DX2D::CText("Text/calibril.ttf_sdf");

	myLinesToDraw.Init(300);
}

void Renderer::AddNodeToDraw(WrappedSprite & aSpriteToAdd)
{
	DX2D::CSprite & tempSprite( *aSpriteToAdd.GetSprite());

	CU::Vector2f tempPosition = aSpriteToAdd.GetPosition();

	tempPosition.x /= static_cast<float>(myWindowSize.x);
	tempPosition.y /= static_cast<float>(myWindowSize.y);

	DX2D::Vector2f drawPosition(tempPosition.x, tempPosition.y);

	tempSprite.SetPosition(drawPosition);

	myNodesToDraw->AddObject(&tempSprite);
}

void Renderer::Draw()
{
	RenderLines();

	myNodesToDraw->Render();
}


void Renderer::ResetRender()
{
	myLinesToDraw.RemoveAll();
	myNodesToDraw->DeleteAll();
	myNodesToDraw->ClearAll();
}

void Renderer::AddLineToDraw(const LineData & aLinkToDraw)
{
	myLinesToDraw.Add(aLinkToDraw);
}

void Renderer::UpdateSprite(WrappedSprite & aSpriteToAdd)
{
	DX2D::CSprite & tempSprite(*aSpriteToAdd.GetSprite());

	CU::Vector2f tempPosition = aSpriteToAdd.GetPosition();

	tempPosition.x /= static_cast<float>(myWindowSize.x);
	tempPosition.y /= static_cast<float>(myWindowSize.y);

	DX2D::Vector2f drawPosition(tempPosition.x, tempPosition.y);

	tempSprite.SetPosition(drawPosition);
}

void Renderer::PrintText(const std::string & aText, const CU::Vector2f & aPosition)
{
	myTextsToPrint->myText = aText;

	CU::Vector2f tempPosition = aPosition;

	tempPosition.x /= myWindowSize.x;
	tempPosition.y /= myWindowSize.y;

	myTextsToPrint->myPosition = DX2D::Vector2f( tempPosition.x, tempPosition.y);
	myTextsToPrint->Render();
}

void Renderer::RenderLines()
{
	for (unsigned short iLine = 0; iLine < myLinesToDraw.Size(); ++iLine)
	{
		RenderLine(myLinesToDraw[iLine]);
	}
	myLinesToDraw.RemoveAll();
}

void Renderer::RenderLine(const LineData & aLineToDraw)
{
	CU::Vector2f startPos = aLineToDraw.myStartPosition;
	CU::Vector2f endPos = aLineToDraw.myEndPosition;

	startPos.x /= static_cast<float>(myWindowSize.x);
	startPos.y /= static_cast<float>(myWindowSize.y);

	endPos.x /= static_cast<float>(myWindowSize.x);
	endPos.y /= static_cast<float>(myWindowSize.y);

	DX2D::Vector2f startPosition(startPos.x, startPos.y);
	DX2D::Vector2f endPosition(endPos.x, endPos.y);
	DX2D::Vector4f color(aLineToDraw.myColor.r, aLineToDraw.myColor.g, aLineToDraw.myColor.b, aLineToDraw.myColor.a);

	DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(startPosition, endPosition, color);
}
