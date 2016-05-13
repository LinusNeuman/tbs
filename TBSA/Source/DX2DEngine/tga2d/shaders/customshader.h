#pragma once
#include <tga2d/math/matrix44.h>
/*
#include <tga2d/render/render_object.h>
#include <d3dcommon.h>
#include <d3d11.h>*/

namespace DX2D
{
	class CTexture;
}
#define MAX_SHADER_DATA 8
#define MAX_SHADER_TEXTURES 1
namespace DX2D
{
	enum EShaderDataID
	{
		EShaderDataID_1,
		EShaderDataID_2,
		EShaderDataID_3,
		EShaderDataID_4,
		EShaderDataID_5,
		EShaderDataID_6,
		EShaderDataID_7,
		EShaderDataID_8,
	};
	enum EShaderTextureSlot
	{
		EShaderTextureSlot_1 = 4, // Below 4 is the standard texture slots, keep above it! (: register( t4 ); in the shader)
	};
	enum EShaderDataBufferIndex
	{
		EShaderDataBufferIndex_1 = 5, // Below 5 is the standard buffer slots, keep above it! (: register(b5) in shader)
	};
    class CDirectEngine;
    class CEngine;
    class CCustomShader
    {
		friend class  CTexturedQuadDrawer;
    public:
		CCustomShader();
		~CCustomShader();


		// Add a float4 to a shader, this must be in the shade file matching 1:1! The Id is the index of the float4 in the shader (top down starting from 0)
		void SetShaderdataFloat4(DX2D::Vector4f someData, EShaderDataID aID);

		// Set a texture to the shader, the index: 0, 1, 2, 3 are reserved. Keep the inder above this and register it with the same id in the shader
		void SetTextureAtRegister(DX2D::CTexture* aTexture, EShaderTextureSlot aRegisterIndex);

		// Run this function after you are done with SetShaderdataFloat4 and SetTextureAtRegister
		// aBufferRegisterIndex is the buffer you register in the shader file. We have used 4 buffers already, so it must be over that, Eg. cbuffer ObjectBufferCustom : register(b5) 
		bool PostInit(const char* aVertex, const char* aPixel, EShaderDataBufferIndex aBufferRegisterIndex = EShaderDataBufferIndex_1);
	protected:
		bool Render(class CRenderObjectSprite* aObject, struct ID3D11Buffer* aObjectBuffer, struct ID3D11Buffer* aVertexBuffer);
    private:
		char AddShaderDataFloat4();
		class CShaderNormal* myShader;
		DX2D::Vector4f myCustomData[MAX_SHADER_DATA];
		int myCurrentDataIndex;
		unsigned char myCurrentTextureIndex;
		bool myIsPostInited;

		struct ID3D11Buffer* myCustomBuffer;
		unsigned char myBufferIndex;

		struct SBoundTexture
		{
			SBoundTexture(){}
			SBoundTexture(DX2D::CTexture* aTex, unsigned char aIndex)
			{
				myTexture = aTex;
				myIndex = aIndex;
			}
			DX2D::CTexture* myTexture;
			unsigned char myIndex;
		};
		SBoundTexture myBoundTextures[MAX_SHADER_TEXTURES];
    };
}