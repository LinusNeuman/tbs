#pragma once
#include "Renderer.h"

class WrappedSprite;

class RenderConverter
{
public:
	RenderConverter();
	~RenderConverter();

	void Init(const CU::Vector2ui & aWindowSize);

	void CalculateAndRenderSprite(const WrappedSprite & aSpriteToRender) const;

	void Draw() const;

private:
	Renderer myRenderer;
};