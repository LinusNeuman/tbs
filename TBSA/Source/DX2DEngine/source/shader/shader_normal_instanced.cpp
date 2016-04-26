#include "stdafx.h"

#include "shaders/shader_normal_instanced.h"
#include "engine.h"
#include "d3d/direct_3d.h"
#include "sprite/textured_quad_batch.h"
#include "sprite/textured_quad.h"
#include "sprite/sprite_batch.h"
#include "sprite/sprite.h"
#include "texture/texture_manager.h"
#include "engine.h"
#include "light/light_manager.h"


using namespace DX2D;


CShaderNormalInstanced::CShaderNormalInstanced(CEngine* aEngine)
	:CShader(aEngine)
{

}

CShaderNormalInstanced::~CShaderNormalInstanced()
{
	for (int i = 0; i < myBufferedObjects.TotalCount(); i++)
	{
		delete myBufferedObjects.myData[i];
	}
}

bool CShaderNormalInstanced::Init()
{
	myBufferedObjects.Init(SPRITE_BATCH_COUNT+1);
	for (int i = 0; i < myBufferedObjects.TotalCount(); i++)
	{
		ObjectBufferInstanceType *text = new ObjectBufferInstanceType();
		myBufferedObjects.myData[i] = text;
	}

	return CreateShaders("shaders/instanced_sprite_shader.fx", "shaders/instanced_sprite_shader.fx");
}

void CShaderNormalInstanced::Render(CTexturedQuadBatch* aObject, ID3D11Buffer* aInstanceBuffer, ID3D11Buffer* aVertexBuffer)
{
	if (!myIsReadyToRender)
	{
		return;
	}
	CShader::Render(aObject);

	for (unsigned int i=0; i< aObject->GetSpriteBatch()->mySprites.size(); i++)
	{
		std::vector<CSprite*>& sprites = aObject->GetSpriteBatch()->mySprites[i];
		int asize = SetShaderParameters(sprites, aObject, aInstanceBuffer, aVertexBuffer);
		myDirect3dEngine->GetContext()->DrawInstanced(6, asize, 0, 0);
	}
}

int CShaderNormalInstanced::SetShaderParameters(std::vector<CSprite*>& someSprites, CTexturedQuadBatch* aBatch, ID3D11Buffer* aInstanceBuffer, ID3D11Buffer* aVertexBuffer)
{
	if(!aInstanceBuffer)
	{
		return 0;
	}

	ID3D11ShaderResourceView* textures[1 + EShaderMap::MAP_MAX];
	textures[0] = aBatch->myTexture->myResource;
	for (unsigned short index = 0; index < EShaderMap::MAP_MAX; index++)
	{
		textures[1 + index] = CEngine::GetInstance()->GetTextureManager().GetDefaultNormalMapResource();
		if (aBatch->myMaps[index])
		{
			textures[1 + index] = aBatch->myMaps[index]->myResource;
		}
	}
	myDirect3dEngine->GetContext()->PSSetShaderResources(1, 1 + EShaderMap::MAP_MAX, textures);


	myBufferedObjects.ResetCount();
	for (CSprite* sprite : someSprites)
	{
		if (!sprite->myShouldRender)
		{
			continue;
		}
		if (!sprite->myShouldRenderBatched)
		{
			continue;
		}


		ObjectBufferInstanceType* next = myBufferedObjects.GetNext();
		if (!next)
		{
			break;
		}

		ObjectBufferInstanceType& type = *next;

		type.myPosition = sprite->GetPosition();
		DX2D::Vector2f offsetPos(DX2D::CEngine::GetInstance()->GetWindowRatio(), -1.0f);
		//type.myPosition = DX2D::Vector2f((type.myPosition.x * 2.0f) - 1.0f, -(type.myPosition.y * 2.0f) + 1.0f);
	
		type.myPosition.x = (type.myPosition.x * 2.0f) - 1.0f;
		type.myPosition.y = -(type.myPosition.y * 2.0f) + 1.0f;

		const DX2D::Vector2f& pivot = sprite->GetPivot();
		type.myPivot.Set(pivot.x, pivot.y, 0, 0);
		type.myRotationAndSize.x = sprite->GetRotation();

		if (sprite->myHasChangedSize)
		{
			type.myRotationAndSize.y = (aBatch->mySize.x * 2) * sprite->myQuad->mySize.x;
			type.myRotationAndSize.z = (aBatch->mySize.y * 2) * sprite->myQuad->mySize.y;
		}
		else
		{
			type.myRotationAndSize.y = aBatch->mySize.x * 2;
			type.myRotationAndSize.z = aBatch->mySize.y * 2;
		}

		type.myRotationAndSize.w = 0;

		STextureRext* rect = sprite->GetTextureRect();
		type.myUVRect.x = rect->myStartX;
		type.myUVRect.y = rect->myStartY;
		type.myUVRect.z = rect->myEndX;
		type.myUVRect.w = rect->myEndY;

		const Vector2f& uv = sprite->GetUVOffset();
		const Vector2f& uvScale = sprite->GetUVScale();
		type.myUV = Vector4f(uv.x, uv.y, uvScale.x, uvScale.y);

		const CColor& color = sprite->GetColor();
		type.myColor.x = color.myR;
		type.myColor.y = color.myG;
		type.myColor.z = color.myB;
		type.myColor.w = color.myA;
	}


	if (myBufferedObjects.NextCount() == -1)
	{
		return 0;
	}

	D3D11_MAPPED_SUBRESOURCE mappedObjectResource;
	HRESULT result = myDirect3dEngine->GetContext()->Map(aInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedObjectResource);
	if(FAILED(result))
	{
		INFO_PRINT("Error in rendering!");
		return 0;
	}


	for (int i = 0; i < myBufferedObjects.NextCount()+1; i++)
	{
		memcpy((ObjectBufferInstanceType*)mappedObjectResource.pData + i, myBufferedObjects.myData[i], sizeof(ObjectBufferInstanceType));
	}

	


	
	myDirect3dEngine->GetContext()->Unmap(aInstanceBuffer, 0);


	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];


	strides[0] = sizeof(SVertexInstanced);
	strides[1] = sizeof(ObjectBufferInstanceType); 

	offsets[0] = 0;
	offsets[1] = 0;

	bufferPointers[0] = aVertexBuffer;	
	bufferPointers[1] = aInstanceBuffer;

	myDirect3dEngine->GetContext()->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);
	return myBufferedObjects.NextCount()+1;
}

bool DX2D::CShaderNormalInstanced::CreateInputLayout(ID3D10Blob* aVS)
{
	D3D11_INPUT_ELEMENT_DESC polygonLayout[9];

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_UINT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "TEXCOORD";
	polygonLayout[2].SemanticIndex = 1;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	polygonLayout[3].SemanticName = "TEXCOORD";
	polygonLayout[3].SemanticIndex = 2;
	polygonLayout[3].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[3].InputSlot = 1;
	polygonLayout[3].AlignedByteOffset = 0;
	polygonLayout[3].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[3].InstanceDataStepRate = 1;

	polygonLayout[4].SemanticName = "TEXCOORD";
	polygonLayout[4].SemanticIndex = 3;
	polygonLayout[4].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[4].InputSlot = 1;
	polygonLayout[4].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[4].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[4].InstanceDataStepRate = 1;

	polygonLayout[5].SemanticName = "TEXCOORD";
	polygonLayout[5].SemanticIndex = 4;
	polygonLayout[5].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[5].InputSlot = 1;
	polygonLayout[5].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[5].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[5].InstanceDataStepRate = 1;

	polygonLayout[6].SemanticName = "TEXCOORD";
	polygonLayout[6].SemanticIndex = 5;
	polygonLayout[6].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[6].InputSlot = 1;
	polygonLayout[6].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[6].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[6].InstanceDataStepRate = 1;

	polygonLayout[7].SemanticName = "TEXCOORD";
	polygonLayout[7].SemanticIndex = 6;
	polygonLayout[7].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[7].InputSlot = 1;
	polygonLayout[7].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[7].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[7].InstanceDataStepRate = 1;

	polygonLayout[8].SemanticName = "TEXCOORD";
	polygonLayout[8].SemanticIndex = 7;
	polygonLayout[8].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[8].InputSlot = 1;
	polygonLayout[8].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[8].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[8].InstanceDataStepRate = 1;

	unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	HRESULT result = myDirect3dEngine->GetDevice()->CreateInputLayout(polygonLayout, numElements, aVS->GetBufferPointer(), aVS->GetBufferSize(), &myLayout);
	if (FAILED(result))
	{
		ERROR_AUTO_PRINT("%s", "Layout error");
	}
	return true;
}
