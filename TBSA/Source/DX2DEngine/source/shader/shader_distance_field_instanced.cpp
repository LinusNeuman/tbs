#include "stdafx.h"

#include "shaders/shader_distance_field_instanced.h"
#include "engine.h"
#include "d3d/direct_3d.h"
#include "sprite/textured_quad_batch.h"
#include "sprite/textured_quad.h"
#include "sprite/sprite_batch.h"
#include "sprite/sprite.h"
#include "texture/texture_manager.h"
#include "engine.h"
#include "math/color.h"

using namespace DX2D;


DX2D::CShaderDistanceFieldInstanced::CShaderDistanceFieldInstanced(CEngine* aEngine)
: CShader(aEngine)
{

}


bool DX2D::CShaderDistanceFieldInstanced::CreateInputLayout(ID3D10Blob* aVS)
{
	D3D11_INPUT_ELEMENT_DESC polygonLayout[8];

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

	unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	HRESULT result = myDirect3dEngine->GetDevice()->CreateInputLayout(polygonLayout, numElements, aVS->GetBufferPointer(), aVS->GetBufferSize(), &myLayout);
	if (FAILED(result))
	{
		ERROR_AUTO_PRINT("%s", "Layout error");
	}
	return true;
}

bool CShaderDistanceFieldInstanced::Init()
{
	return CreateShaders("shaders/instanced_distance_shader.fx", "shaders/instanced_distance_shader.fx");
}

void CShaderDistanceFieldInstanced::Render(CTexturedQuadBatch* aObject, ID3D11Buffer* aInstanceBuffer, ID3D11Buffer* aVertexBuffer)
{
	if (!myIsReadyToRender)
	{
		return;
	}
	CShader::Render(aObject);
	CDirectEngine& engine = CEngine::GetInstance()->GetDirect3D();
	for (unsigned int i=0; i< aObject->GetSpriteBatch()->mySprites.size(); i++)
	{
		std::vector<CSprite*>& sprites = aObject->GetSpriteBatch()->mySprites[i];
		SetShaderParameters(sprites, aObject, aInstanceBuffer, aVertexBuffer);
		int asize = (int)sprites.size();
		engine.GetContext()->DrawInstanced(6, asize, 0, 0);
	}
}

void CShaderDistanceFieldInstanced::SetShaderParameters(std::vector<CSprite*>& someSprites, CTexturedQuadBatch* aBatch, ID3D11Buffer* aInstanceBuffer, ID3D11Buffer* aVertexBuffer)
{
	if(!aInstanceBuffer)
	{
		return;
	}

	myBufferedObjects.clear();
	myBufferedObjects.reserve(someSprites.size());
	const float ratioX = (float)myDirect3dEngine->myWindowSize.x / (float)myDirect3dEngine->myWindowSize.y;
	for (unsigned int i = 0; i < someSprites.size(); i++)
	{
		CSprite* sprite = someSprites[i];

		if (!sprite->GetShouldRender())
		{
			continue;
		}
		if (!sprite->myShouldRenderBatched)
		{
			continue;
		}

		ObjectBufferInstanceType type;

		type.myPosition = sprite->GetPosition();
		DX2D::Vector2f offsetPos(1.0f, -1.0f);
		Vector2f correctedPosition = DX2D::Vector2f(type.myPosition.x * 2.0f, -type.myPosition.y * 2.0f) - offsetPos;
		type.myPosition = correctedPosition;

		type.myPivot.Set(sprite->GetPivot().x, sprite->GetPivot().y, 0, 0);
		type.myPosition.x *= ratioX;
		type.myRotationAndSize.x = sprite->GetRotation();

		if (sprite->HasChangedSize())
		{
			CTexturedQuad* texQuad = sprite->GetTexturedQuad();
			//myQuad->mySize * myQuad->mySizeMultiplier
			type.myRotationAndSize.y = texQuad->mySize.x * texQuad->mySizeMultiplier.x;
			type.myRotationAndSize.z = texQuad->mySize.y * texQuad->mySizeMultiplier.y;
		}
		else
		{
			type.myRotationAndSize.y = aBatch->mySize.x;
			type.myRotationAndSize.z = aBatch->mySize.y;
		}

		// Crispiness of distance field
		type.myRotationAndSize.w = (1.0f - type.myRotationAndSize.y) * 0.1f;



		Vector2f uv = sprite->GetUVOffset();
		type.myUV = Vector4f(uv.x, uv.y, sprite->GetUVScale().x, sprite->GetUVScale().y);

		const CColor& color = sprite->GetColor();
		//type.myColor = sprite->GetColor().AsVec4();
		type.myColor.x = color.myR;
		type.myColor.y = color.myG;
		type.myColor.z = color.myB;
		type.myColor.w = color.myA;
		myBufferedObjects.push_back(type);
	}

	D3D11_MAPPED_SUBRESOURCE mappedObjectResource;
	HRESULT result = myDirect3dEngine->GetContext()->Map(aInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedObjectResource);
	if(FAILED(result))
	{
		INFO_PRINT("Error in rendering!");
		return;
	}

	if (myBufferedObjects.size() == 0)
	{
		return;
	}

	memcpy(mappedObjectResource.pData, &myBufferedObjects[0], sizeof(ObjectBufferInstanceType) * myBufferedObjects.size());

	myDirect3dEngine->GetContext()->Unmap(aInstanceBuffer, 0);
	myDirect3dEngine->GetContext()->PSSetShaderResources(1, 1, &aBatch->myTexture->myResource);



	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = sizeof(SVertexInstanced); 
	strides[1] = sizeof(ObjectBufferInstanceType); 
	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	bufferPointers[0] = aVertexBuffer;	
	bufferPointers[1] = aInstanceBuffer;

	myDirect3dEngine->GetContext()->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

}