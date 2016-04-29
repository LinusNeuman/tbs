#pragma once
#include <tga2d/sprite/sprite.h>

class RenderCommand
{
public:
	RenderCommand();
	RenderCommand(DX2D::CSprite & aSpriteToRender, CU::Vector2f & aPosition);
	~RenderCommand();

	void Render() const;

	
	CU::Vector2f myPosition;

private:
	DX2D::CSprite * mySprite;
};

