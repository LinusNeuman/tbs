#pragma once
#include "RenderCommand.h"

namespace DX2D
{
	class CSpriteBatch;
	class CSprite;
	class CText;
}

class WrappedSprite;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();
	
	void Draw() const;

	void SetWindowSize(const CU::Vector2ui & aWindowSize);

	void AddRenderCommand(RenderCommand & aRenderCommand);

	void SwapBuffer();

private:
	CU::GrowingArray<RenderCommand> * myBuffer;
	CU::GrowingArray<RenderCommand> * myCommandsToRender;

	CU::Vector2ui myWindowSize;

	void RenderAllSprites() const;
};

inline void Renderer::SetWindowSize(const CU::Vector2ui & aWindowSize)
{
	myWindowSize = aWindowSize;
}