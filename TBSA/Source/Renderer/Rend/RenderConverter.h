#pragma once
#include "Renderer.h"

class WrappedSprite;

class RenderConverter
{
public:
	RenderConverter();
	~RenderConverter();

	void Init(const std::string & aSpriteFilePath, const CU::Vector2ui & aWindowSize);

	void AddSpriteToBeDraw(WrappedSprite & aSprite);

	void UpdateSprite(WrappedSprite & aSpriteToUpdate);

	void CalculateAndRenderSprite(const WrappedSprite & aSpriteToRender) const;

	void Draw() const;

private:
	Renderer myRenderer;
};