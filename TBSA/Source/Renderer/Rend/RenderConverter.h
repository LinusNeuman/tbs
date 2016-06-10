#pragma once
#include "Rend/Renderer.h"
#include <PostMaster/MessageReceiver.h>

class StaticSprite;
class Camera2D;

class RenderConverter : public MessageReciever
{
public:
	static void Create();
	static void Destroy();

	static void Init(const CU::Vector2ui & aWindowSize);

	static void CalculateAndRenderIso(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition);
	static void CalculateAndRenderSprite(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition);

	static void AddRenderCommand(RenderCommand & aRenderCommand);
	static void DrawLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition, const CU::Vector4f & aColor = CU::Vector4f::One);
	static void DrawIsometricLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition, const CU::Vector4f & aColor = CU::Vector4f::One);

	static void Draw();
	//static void SetCamera(const Camera2D & aCamera);

	static void SwapBuffers();
	static void ClearCommands();

	virtual bool RecieveMessage(const LevelTileMetricsMessage & aMessage) override;
	virtual bool RecieveMessage(const SetMainCameraMessage & aMessage) override;

	

private:
	RenderConverter();
	~RenderConverter();

	static RenderConverter * ourInstance;

	static RenderConverter & GetInstance();

	const Camera2D * myCamera;

	CU::Vector2ui myLevelTileLayout;
	Renderer myRenderer;
};

inline RenderConverter & RenderConverter::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "RenderConverter Singleton instance is nullptr");
	return *ourInstance;
}


#define DRAWLINE(aStartPosition, aEndPosition) RenderConverter::DrawLine((aStartPosition),(aEndPosition));
#define DRAWISOMETRICLINE(aStartPosition, aEndPosition) RenderConverter::DrawIsometricLine((aStartPosition),(aEndPosition));