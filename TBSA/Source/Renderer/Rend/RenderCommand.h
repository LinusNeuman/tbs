#pragma once
#include <tga2d/sprite/sprite.h>

class RenderCommand
{
public:
	RenderCommand();
	RenderCommand(DX2D::CSprite & aSpriteToRender, CU::Vector2f & aPosition, const float aPriority);
	~RenderCommand();

	void Render() const;
	float GetPriority()
	{
		return myRenderPriority;
	}
	
	CU::Vector2f myPosition;

private:
	float myRenderPriority;
	DX2D::CSprite * mySprite;
};

