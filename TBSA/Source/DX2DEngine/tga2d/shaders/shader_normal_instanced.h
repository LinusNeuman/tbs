#pragma once

#include "shaders/shader.h"
#include "shaders/shader_common.h"
#include "arrays/simple_pointer_array.h"

namespace DX2D
{
	class CTexturedQuadBatch;
	class CSprite;
	class CShaderNormalInstanced : public CShader
	{
	public:
		CShaderNormalInstanced(CEngine* aEngine);
		~CShaderNormalInstanced();
		bool Init() override;
		void Render(CTexturedQuadBatch* aObject, ID3D11Buffer* aInstanceBuffer, ID3D11Buffer* aVertexBuffer);
		bool CreateInputLayout(ID3D10Blob* aVS) override;
	protected:
	private:
		int SetShaderParameters(std::vector<CSprite*>& someSprites, CTexturedQuadBatch* aBatch, ID3D11Buffer* aInstanceBuffer, ID3D11Buffer* aVertexBuffer);
		//std::vector<ObjectBufferInstanceType*> myBufferedObjects;
		SSimplePointerArray<ObjectBufferInstanceType*> myBufferedObjects;
	};
}