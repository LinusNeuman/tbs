#pragma once

class WrappedSprite;

class RenderConverter
{
public:
	RenderConverter();
	~RenderConverter();

	void CalculateAndRenderSprite(const WrappedSprite & aSpriteToRender);
};

