#pragma once
#include "Renderer.h"

class WrappedSprite;

class RenderConverter
{
public:
	RenderConverter();
	~RenderConverter();

	void Init(const CU::Vector2ui & aWindowSize);

	void CalculateAndRenderIso(const WrappedSprite & aSpriteToRender, const CU::Vector2f & aPosition);
	void CalculateAndRenderSprite(const WrappedSprite & aSpriteToRender, const CU::Vector2f & aPosition);

	void AddRenderCommand(RenderCommand & aRenderCommand);

	void Draw() const;

	void SwapBuffers();

private:
	

	Renderer myRenderer;
};