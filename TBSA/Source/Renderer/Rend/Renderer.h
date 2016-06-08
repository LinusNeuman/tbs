#pragma once
#include <CU/Vectors/vector2.h>
#include <CU/Vectors/vector4.h>

namespace DX2D
{
	class CSpriteBatch;
	class CSprite;
	class CText;
}

class StaticSprite;
class RenderCommand;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();
	void Draw() const;
	void SetWindowSize(const CU::Vector2ui & aWindowSize);
	void AddRenderCommand(RenderCommand & aRenderCommand);
	void DrawLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition, const CU::Vector4f & aColor = CU::Vector4f::One ,bool OffsetToMiddle = false);
	void SwapBuffer();

private:
	CommonUtilities::GrowingArray<CommonUtilities::GrowingArray<RenderCommand>> * myBuffer;
	CommonUtilities::GrowingArray<CommonUtilities::GrowingArray<RenderCommand>> * myCommandsToRender;

	CU::Vector2ui myWindowSize;

	void RenderAllSprites() const;
};

inline void Renderer::SetWindowSize(const CU::Vector2ui & aWindowSize)
{
	myWindowSize = aWindowSize;
}