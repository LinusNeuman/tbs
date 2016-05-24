#include "stdafx.h"
#include "shaders/shader_normal.h"
#include "shaders/customshader.h"
#include "shaders/shader_common.h"
#include "texture/texture.h"

#include <tga2d/render/render_object.h>
#include <d3dcommon.h>
#include <d3d11.h>

DX2D::CCustomShader::CCustomShader()
{
	myShader = nullptr;
	myCurrentDataIndex = -1;
	myIsPostInited = false;
	myBufferIndex = 0;
	myCurrentTextureIndex = 0;
}

DX2D::CCustomShader::~CCustomShader()
{
	delete myShader;
	myShader = nullptr;

	//SAFE_RELEASE(myCustomBuffer);

}

bool DX2D::CCustomShader::PostInit(const char* aVertex, const char* aPixel, EShaderDataBufferIndex aBufferRegisterIndex)
{
	if (myCurrentDataIndex < 0)
	{
		ERROR_PRINT("DX2D::CCustomShader::PostInit - No data to init with!");
		return false;
	}
	if (aBufferRegisterIndex <= EConstantBufferSlot_MAX - 1)
	{
		ERROR_PRINT("DX2D::CCustomShader::PostInit - buffer index can not be below the standard buffers in index!");
		return false;
	}
	myShader = new CShaderNormal(CEngine::GetInstance());
	if (!myShader->CreateShaders(aVertex, aPixel) )
	{
		delete myShader;
		myShader = nullptr;
		return false;
	}

	D3D11_BUFFER_DESC commonBufferDesc;
	commonBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	commonBufferDesc.ByteWidth = sizeof(DX2D::Vector4f) * (myCurrentDataIndex+1);
	commonBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	commonBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	commonBufferDesc.MiscFlags = 0;
	commonBufferDesc.StructureByteStride = 0;

	HRESULT result = CEngine::GetInstance()->GetDirect3D().GetDevice()->CreateBuffer(&commonBufferDesc, NULL, &myCustomBuffer);
	if (result != S_OK)
	{
		ERROR_PRINT("DX2D::CCustomShader::PostInit - Size missmatch between CPU and GPU(shader)");
		return false;
	}
	myBufferIndex = (unsigned char)aBufferRegisterIndex;
	myIsPostInited = true;
	return true;
}


bool DX2D::CCustomShader::Render(CRenderObjectSprite* aObject, ID3D11Buffer* aObjectBuffer, ID3D11Buffer* aVertexBuffer)
{
	if (!myIsPostInited)
	{
		ERROR_PRINT("DX2D::CCustomShader::Render - Custom shader is not inited! Run PostInit() on this shader!");
		return false;
	}

	ID3D11DeviceContext* context = CEngine::GetInstance()->GetDirect3D().GetContext();

	D3D11_MAPPED_SUBRESOURCE mappedResourceCommon;
	DX2D::Vector4f* dataPtrCommon;
	HRESULT result = context->Map(myCustomBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResourceCommon);
	if (FAILED(result))
	{
		INFO_PRINT("Error in rendering!");
		return false;
	}

	dataPtrCommon = (DX2D::Vector4f*)mappedResourceCommon.pData;
	for (int i = 0; i < myCurrentDataIndex+1; i++)
	{
		dataPtrCommon[i].x = myCustomData[i].x;
		dataPtrCommon[i].y = myCustomData[i].y;
		dataPtrCommon[i].z = myCustomData[i].z;
		dataPtrCommon[i].w = myCustomData[i].w;
	}
	
	context->Unmap(myCustomBuffer, 0);
	context->VSSetConstantBuffers(myBufferIndex, 1, &myCustomBuffer);
	context->PSSetConstantBuffers(myBufferIndex, 1, &myCustomBuffer);

	for (int i = 0; i < myCurrentTextureIndex; i++)
	{
		ID3D11ShaderResourceView* textures[1];
		textures[0] = myBoundTextures[i].myTexture->myResource;

		context->PSSetShaderResources(myBoundTextures[i].myIndex, 1, textures);
	}

	myShader->Render(aObject, aObjectBuffer, aVertexBuffer);
	return true;
}

void DX2D::CCustomShader::SetShaderdataFloat4(DX2D::Vector4f someData, EShaderDataID aID)
{
	if (aID > MAX_SHADER_DATA)
	{
		ERROR_PRINT("DX2D::CCustomShader::SetShaderdataFloat4() The id is bigger than allowed size");
		return;
	}
	myCustomData[aID] = someData;
	if (aID > myCurrentDataIndex)
	{
		myCurrentDataIndex = aID;
	}
}

void DX2D::CCustomShader::SetTextureAtRegister(DX2D::CTexture* aTexture, EShaderTextureSlot aRegisterIndex)
{
	if (aRegisterIndex < 4)
	{
		ERROR_PRINT("DX2D::CCustomShader::SetTextureAtRegister - Index below 4 is not allowed as they are reserve.");
		return;
	}
	if (myCurrentTextureIndex >= MAX_SHADER_TEXTURES)
	{
		ERROR_PRINT("DX2D::CCustomShader::SetTextureAtRegister - Too many textures already bound!");
		return;
	}
	myBoundTextures[myCurrentTextureIndex] = SBoundTexture(aTexture, (unsigned char)aRegisterIndex);
	myCurrentTextureIndex++;
}

