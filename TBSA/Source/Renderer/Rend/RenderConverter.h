#pragma once
#include "Renderer.h"

class WrappedSprite;

class RenderConverter
{
public:
	static void Create();
	static void Destroy();

	static void Init(const CU::Vector2ui & aWindowSize);

	static void CalculateAndRenderIso(const WrappedSprite & aSpriteToRender, const CU::Vector2f & aPosition);
	static void CalculateAndRenderSprite(const WrappedSprite & aSpriteToRender, const CU::Vector2f & aPosition);

	static void AddRenderCommand(RenderCommand & aRenderCommand);

	static void Draw();

	static void SwapBuffers();

private:
	RenderConverter();
	~RenderConverter();

	static RenderConverter * ourInstance;

	static RenderConverter & GetInstance();

	Renderer myRenderer;
};

inline RenderConverter & RenderConverter::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "RenderConverter Singleton instance is nullptr");
	return *ourInstance;
}
