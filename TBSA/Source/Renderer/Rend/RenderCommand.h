#pragma once
#include <tga2d/sprite/sprite.h>

class RenderCommand
{
public:
	RenderCommand();
	RenderCommand(DX2D::CSprite & aSpriteToRender, CU::Vector2f & aPosition, const float aPriority, const USHORT aLayer);
	~RenderCommand();

	void Render() const;
	float GetPriority()
	{
		return myRenderPriority;
	}

	USHORT GetLayer()
	{
		return myLayer;
	}
	
	CU::Vector2f myPosition;

private:
	USHORT myLayer;
	float myRenderPriority;
	DX2D::CSprite * mySprite;
};

