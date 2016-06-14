#include "stdafx.h"
#include "RenderConverter.h"
#include <tga2d/sprite/sprite.h>
#include "StaticSprite.h"
#include <CU/Vectors/vector2.h>
#include <CU/Utility/Math/Isometric.h>

#include <PostMaster/SingletonPostMaster.h>
#include "Rend/RenderCommand.h"
#include <CU/Camera/Camera2D.h>

#include <Message/LevelTileMetricsMessage.h>
#include <Message/SetMainCameraMessage.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

RenderConverter * RenderConverter::ourInstance = nullptr;



//const float TileWidth = 10;
const float TileSize = 128.f;
const float TileSizeHalf = 64.f;

RenderConverter::RenderConverter()
{
}


RenderConverter::~RenderConverter()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eLevelTileLayoutSettings, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eCamera, *this);
}



void RenderConverter::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new RenderConverter();
	}
}

void RenderConverter::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}

void RenderConverter::Init(const CU::Vector2ui & aWindowSize)
{
	GetInstance().myRenderer.Init();
	GetInstance().myRenderer.SetWindowSize(aWindowSize);
	GetInstance().myWindowSize = aWindowSize;

	GetInstance().myLevelTileLayout = CU::Vector2ui(10, 10);

	SingletonPostMaster::AddReciever(RecieverTypes::eCamera, GetInstance());
	SingletonPostMaster::AddReciever(RecieverTypes::eLevelTileLayoutSettings, GetInstance());
}


void RenderConverter::CalculateAndRenderIso(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	CU::Vector2f tempPosition = aPosition * (*GetInstance().myCamera).GetInverse();

	const float Priority = (tempPosition.x + (tempPosition.y * static_cast<float>(GetInstance().myLevelTileLayout.x))) + aSpriteToRender.GetRenderPriority() / 10000.f;

	CU::Vector2f newPos = CU::IsometricToPixel(tempPosition);

	newPos.x /= FLOATCAST(SingletonDataHolder::GetTargetResolution().x);
	newPos.y /= FLOATCAST(SingletonDataHolder::GetTargetResolution().y);

	float renderScale = FLOATCAST(SingletonDataHolder::GetTargetResolution().y) / (1080.f);
	newPos *= renderScale;

	newPos.x += 0.5f;
	newPos.y += 0.5f;

	GetInstance().myRenderer.AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), newPos, Priority, static_cast<USHORT>(aSpriteToRender.GetLayer()), aSpriteToRender.GetRenderData()));
}

void RenderConverter::CalculateAndRenderSprite(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	CU::Vector2f newPos(aPosition);
	newPos.x /= FLOATCAST(SingletonDataHolder::GetTargetResolution().x);
	newPos.y /= FLOATCAST(SingletonDataHolder::GetTargetResolution().y);
	GetInstance().AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), newPos, aSpriteToRender.GetRenderPriority(), static_cast<USHORT>(aSpriteToRender.GetLayer()), aSpriteToRender.GetRenderData()));
}

void RenderConverter::RenderSpriteNormalized(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	GetInstance().AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), aPosition, aSpriteToRender.GetRenderPriority(), static_cast<USHORT>(aSpriteToRender.GetLayer()), aSpriteToRender.GetRenderData()));
}

void RenderConverter::AddRenderCommand(RenderCommand & aRenderCommand)
{
	GetInstance().myRenderer.AddRenderCommand(aRenderCommand);
}

void RenderConverter::AddRenderCommandPutInCameraSpaceAndNormalize(RenderCommand & aRenderCommand)
{
	CU::Vector2f tempPosition = aRenderCommand.myPosition * (*GetInstance().myCamera).GetInverse();

	CU::Vector2f newPos = CU::IsometricToPixel(tempPosition);

	newPos.x /= FLOATCAST(GetInstance().myWindowSize.x);
	newPos.y /= FLOATCAST(GetInstance().myWindowSize.y);

	float renderScale = FLOATCAST(SingletonDataHolder::GetTargetResolution().y) / (1080.f);
	newPos *= renderScale;

	newPos.x += 0.5f;
	newPos.y += 0.5f;

	aRenderCommand.myPosition = newPos;

	GetInstance().myRenderer.AddRenderCommand(aRenderCommand);
}

void RenderConverter::DrawLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition, const CU::Vector4f & aColor /*= CU::Vector4f::One*/)
{
	GetInstance().myRenderer.DrawLine(aStartPosition, aEndPosition, aColor);
}

void RenderConverter::ClearCommands()
{
	GetInstance().myRenderer.ClearCommands();
}

void RenderConverter::DrawIsometricLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition, const CU::Vector4f & aColor /*= CU::Vector4f::One*/)
{
	CU::Vector2f newStartPos = CU::IsometricToPixel(aStartPosition * (*GetInstance().myCamera).GetInverse());

	CU::Vector2f newEndPos = CU::IsometricToPixel(aEndPosition * (*GetInstance().myCamera).GetInverse());

	float renderScale = FLOATCAST(SingletonDataHolder::GetTargetResolution().y) / (1080.f);

	GetInstance().myRenderer.DrawLine(newStartPos * renderScale, newEndPos * renderScale, aColor, true);
}

void RenderConverter::Draw()
{
	GetInstance().myRenderer.Draw();
}

void RenderConverter::SwapBuffers()
{
	GetInstance().myRenderer.SwapBuffer();
}

bool RenderConverter::RecieveMessage(const LevelTileMetricsMessage & aMessage)
{
	myLevelTileLayout = aMessage.myWidthHeight;
	return true;
}

bool RenderConverter::RecieveMessage(const SetMainCameraMessage & aMessage)
{
	myCamera = &aMessage.myCamera;
	return true;
}
