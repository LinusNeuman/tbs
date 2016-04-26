#pragma once

#include "shader.h"
#include "shader_common.h"

namespace DX2D
{

	class CTexturedQuadBatch;
	class CSprite;
	class CShaderDistanceFieldInstanced : public CShader
	{
	public:
		CShaderDistanceFieldInstanced(CEngine* aEngine);
		bool Init() override;
		void Render(CTexturedQuadBatch* aObject, ID3D11Buffer* aInstanceBuffer, ID3D11Buffer* aVertexBuffer);
		bool CreateInputLayout(ID3D10Blob* aVS) override;
	protected:
	private:
		void SetShaderParameters(std::vector<CSprite*>& someSprites, CTexturedQuadBatch* aBatch, ID3D11Buffer* aInstanceBuffer, ID3D11Buffer* aVertexBuffer);
		std::vector<ObjectBufferInstanceType> myBufferedObjects;
	};
}