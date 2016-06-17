#pragma once

#include "shader.h"
#include "shader_common.h"

namespace DX2D
{
	struct ObjectBufferType
	{
		Vector4f myRotationAndSize;
		Vector2f myPosition;
		Vector2f myUnUsed2;
		Vector4f myColor;
		Vector4f myPivot;
		Vector4f myUV;
	};


	class CRenderObjectSprite;
	class CTexturedQuad;
	class CShaderNormal : public CShader
	{
	public:
		CShaderNormal(CEngine* aEngine);
		~CShaderNormal();

		bool Init() override;
		void Render(CRenderObjectSprite* aObject, ID3D11Buffer* aObjectBuffer, ID3D11Buffer* aVertexBuffer);
		bool CreateInputLayout(ID3D10Blob* aVS) override;
	private:
		void SetShaderParameters(CRenderObjectSprite* aObject, ID3D11Buffer* aObjectBuffer, ID3D11Buffer* aVertexBuffer);
		void UpdateVertexes(CTexturedQuad* aQuad, ID3D11Buffer* aVertexBuffer);
	};

}