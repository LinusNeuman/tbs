#include "stdafx.h"

#include "shaders/shader.h"
#include "engine.h"
#include "d3d/direct_3d.h"
#include "light/light.h"
#include "light/light_manager.h"
#include "shaders/shader_common.h"
#include "filewatcher/file_watcher.h"
#include "texture/texture_manager.h"

DX2D::CShader::CShader(CEngine* aEngine)
	:myEngine(aEngine)
	, myDirect3dEngine(&aEngine->GetDirect3D())
	, myMatrixBuffer(0)
	, myLightBuffer(0)
	, myCommonBuffer(0)
	, myIsListeningOnFileChange(false)
	, myRandomSeed(rand() % 100)
{
	myIsReadyToRender = false;
}

DX2D::CShader::~CShader()
{
	SAFE_RELEASE(myVertexShader);
	SAFE_RELEASE(myPixelShader);
	SAFE_RELEASE(myLayout);
	SAFE_RELEASE(myMatrixBuffer);
	SAFE_RELEASE(myLightBuffer);
	SAFE_RELEASE(myCommonBuffer);
	
}

bool DX2D::CShader::CreateShaders(const char* aVertex, const char* aPixel, callback_layout aLayout)
{
	myIsReadyToRender = false;
	myVertexShaderFile = aVertex;
	myPixelShaderFile = aPixel;

	if (!myIsListeningOnFileChange)
	{

		myEngine->GetFileWatcher()->WatchFileChangeWithDependencies(DX2D::CharArrayToLPCWSTR(aPixel), std::bind(&DX2D::CShader::OnShaderFileModified, this, std::placeholders::_1));
	
		
		myIsListeningOnFileChange = true;
	}

	ID3D10Blob *VS = nullptr;
	ID3D10Blob *PS = nullptr;
	INFO_PRINT("%s%s", "Initing vertex Shader: ", aVertex);
	INFO_PRINT("%s%s", "Initing pixel Shader: ", aPixel);

	if (myEngine->GetDirect3D().GetFeatureLevel() == D3D_FEATURE_LEVEL_10_1)
	{
		if (!myEngine->GetDirect3D().CompileShader(aVertex, "VShader", "vs_4_0", VS))
		{
			ERROR_AUTO_PRINT("%s%s", "Shader error in file: ", aVertex);
			return false;
		}
		if (!myEngine->GetDirect3D().CompileShader(aPixel, "PShader", "ps_4_0", PS))
		{
			ERROR_AUTO_PRINT("%s%s", "Shader error in file: ", aPixel);
			return false;
		}
	}
	else
	{
		if (!myEngine->GetDirect3D().CompileShader(aVertex, "VShader", "vs_5_0", VS))
		{
			ERROR_AUTO_PRINT("%s%s", "Shader error in file: ", aVertex);
			return false;
		}
		if (!myEngine->GetDirect3D().CompileShader(aPixel, "PShader", "ps_5_0", PS))
		{
			ERROR_AUTO_PRINT("%s%s", "Shader error in file: ", aPixel);
			return false;
		}
	}

	
	HRESULT resultVS = myEngine->GetDirect3D().GetDevice()->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &myVertexShader);
	if (resultVS != 0)
	{
		ERROR_PRINT("%s%s", "Could not create vertex shader: ", aVertex);
	}
	HRESULT resultPS = myEngine->GetDirect3D().GetDevice()->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &myPixelShader);
	if (resultPS != 0)
	{
		ERROR_PRINT("%s%s", "Could not create pixel shader: ", aVertex);
	}

	if (myLayout)
	{
		myLayout->Release();
		myLayout = nullptr;
	}

	if (aLayout)
	{
		aLayout(VS);
	}
	else if (!CreateInputLayout(VS))
	{
		// LAYOUT
		D3D11_INPUT_ELEMENT_DESC polygonLayout[7];

		polygonLayout[0].SemanticName = "POSITION";
		polygonLayout[0].SemanticIndex = 0;
		polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygonLayout[0].InputSlot = 0;
		polygonLayout[0].AlignedByteOffset = 0;
		polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[0].InstanceDataStepRate = 0;

		polygonLayout[1].SemanticName = "TEXCOORD";
		polygonLayout[1].SemanticIndex = 0;
		polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		polygonLayout[1].InputSlot = 0;
		polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[1].InstanceDataStepRate = 0;

		polygonLayout[2].SemanticName = "TEXCOORD";
		polygonLayout[2].SemanticIndex = 1;
		polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		polygonLayout[2].InputSlot = 1;
		polygonLayout[2].AlignedByteOffset = 0;
		polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
		polygonLayout[2].InstanceDataStepRate = 1;

		polygonLayout[3].SemanticName = "TEXCOORD";
		polygonLayout[3].SemanticIndex = 2;
		polygonLayout[3].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		polygonLayout[3].InputSlot = 1;
		polygonLayout[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
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


		unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

		// Create the vertex input layout.
		HRESULT result = myEngine->GetDirect3D().GetDevice()->CreateInputLayout(polygonLayout, numElements, VS->GetBufferPointer(), VS->GetBufferSize(), &myLayout);
		if (FAILED(result))
		{
			ERROR_AUTO_PRINT("%s", "Layout error");
			return false;
		}
	}

	VS->Release();
	VS = 0;

	PS->Release();
	PS = 0;

	if (myMatrixBuffer)
	{
		myMatrixBuffer->Release();
		myMatrixBuffer = nullptr;
	}


	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	HRESULT result = S_OK;
	result = myEngine->GetDirect3D().GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &myMatrixBuffer);

	if (myCommonBuffer)
	{
		myCommonBuffer->Release();
		myCommonBuffer = nullptr;
	}

	D3D11_BUFFER_DESC commonBufferDesc;
	commonBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	commonBufferDesc.ByteWidth = sizeof(CommonBufferType);
	commonBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	commonBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	commonBufferDesc.MiscFlags = 0;
	commonBufferDesc.StructureByteStride = 0;

	result = myEngine->GetDirect3D().GetDevice()->CreateBuffer(&commonBufferDesc, NULL, &myCommonBuffer);

	// LIGHTS
	D3D11_BUFFER_DESC lightBufferDesc;
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	if (myLightBuffer)
	{
		myLightBuffer->Release();
		myLightBuffer = nullptr;
	}
	myEngine->GetDirect3D().GetDevice()->CreateBuffer(&lightBufferDesc, NULL, &myLightBuffer);

	
	myIsReadyToRender = true;
	return true;
}

void DX2D::CShader::OnShaderFileModified(std::wstring aFile)
{
	INFO_PRINT("%s", "Shader modified! Trying to reload...");

	// Test compile
	ID3D10Blob *VS = nullptr;
	ID3D10Blob *PS = nullptr;
	if (!myEngine->GetDirect3D().CompileShader(myVertexShaderFile.c_str(), "VShader", "vs_5_0", VS))
	{
		ERROR_AUTO_PRINT("%s%s", "Shader modified failed! error in file: ", myVertexShaderFile.c_str());
		return;
	}
	if (!myEngine->GetDirect3D().CompileShader(myPixelShaderFile.c_str(), "PShader", "ps_5_0", PS))
	{
		ERROR_AUTO_PRINT("%s%s", "Shader modified failed! error in file: ", myPixelShaderFile.c_str());
		return;
	}

	VS->Release();
	PS->Release();

	if (myPixelShader)
	{
		myPixelShader->Release();
		myPixelShader = nullptr;
		
	}
	if (myVertexShader)
	{
		myVertexShader->Release();
		myVertexShader = nullptr;
	}

	CreateShaders(myVertexShaderFile.c_str(), myPixelShaderFile.c_str());

}

bool DX2D::CShader::Render(CRenderObject* aObject)
{
	if (!myVertexShader || !myPixelShader || !myIsReadyToRender)
	{
		return false;
	}
	CDirectEngine& engine = myEngine->GetDirect3D();
	engine.GetContext()->VSSetShader(myVertexShader, NULL, 0);
	engine.GetContext()->PSSetShader(myPixelShader, NULL, 0);
	engine.GetContext()->IASetInputLayout(myLayout);
	engine.GetContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	ID3D11ShaderResourceView* textures[1];
	textures[0] = myEngine->GetTextureManager().GetNoiseTexture();
	engine.GetContext()->PSSetShaderResources(0, 1, textures);
	DoOneFrameUpdates(aObject);

	return true;
}

void DX2D::CShader::DoOneFrameUpdates(CRenderObject* aObject)
{
	CDirectEngine& engine = myEngine->GetDirect3D();

	if (!myMatrixBuffer || !myCommonBuffer)
	{
		return;
	}
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;

	HRESULT result;
	result = engine.GetContext()->Map(myMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		INFO_PRINT("Error in rendering!");
		return;
	}

	dataPtr = (MatrixBufferType*)mappedResource.pData;

	static const Matrix44 identityMatrix;

	Matrix44 temp = myEngine->GetDirect3D().myWorldWatrix;
	if (aObject->myIsScreenSpace)
	{
		temp = identityMatrix;
	}
	
	temp.Transpose();
	dataPtr->world = temp;

	dataPtr->view = myEngine->GetDirect3D().myViewWatrix;

	Matrix44 temp2 = myEngine->GetDirect3D().myProjWatrix;
	temp2.Transpose();
	dataPtr->projection = temp2;




	engine.GetContext()->Unmap(myMatrixBuffer, 0);
	engine.GetContext()->VSSetConstantBuffers(EConstantBufferSlot_Matrix, 1, &myMatrixBuffer);
	engine.GetContext()->PSSetConstantBuffers(EConstantBufferSlot_Matrix, 1, &myMatrixBuffer);


	D3D11_MAPPED_SUBRESOURCE mappedResourceCommon;
	CommonBufferType* dataPtrCommon;
	result = engine.GetContext()->Map(myCommonBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResourceCommon);
	if (FAILED(result))
	{
		INFO_PRINT("Error in rendering!");
		return;
	}

		dataPtrCommon = (CommonBufferType*)mappedResourceCommon.pData;
	dataPtrCommon->myResolution = Vector4f(static_cast<float>(myEngine->GetRenderSize().x), static_cast<float>(myEngine->GetRenderSize().y), 0, 0);
	dataPtrCommon->myTimings.x = CEngine::GetInstance()->myTotalTime;
	dataPtrCommon->myTimings.y = CEngine::GetInstance()->myDeltaTime;
	dataPtrCommon->myRandomValues.x = static_cast<float>(myRandomSeed);
	dataPtrCommon->myRandomValues.y = (static_cast<float>(((rand() % 2000) - 1000)) / 1000.0f);


	engine.GetContext()->Unmap(myCommonBuffer, 0);
	engine.GetContext()->VSSetConstantBuffers(EConstantBufferSlot_Common, 1, &myCommonBuffer);
	engine.GetContext()->PSSetConstantBuffers(EConstantBufferSlot_Common, 1, &myCommonBuffer);


	// LIGHTS
	if (!myLightBuffer)
	{
		return;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResourceLight;
	LightBufferType* dataPtrLights;

	result = engine.GetContext()->Map(myLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResourceLight);
	if (FAILED(result))
	{
		INFO_PRINT("Error in rendering!");
		return;
	}

	std::vector<const CLight*> lights = myEngine->GetLightManager().myLightsToRender;
	dataPtrLights = (LightBufferType*)mappedResourceLight.pData;
	dataPtrLights->myNumberOfLights = lights.size();

	for (unsigned int i = 0; i < 4; i++)
	{
		dataPtrLights->myLights[i].myLightColors.Set(0, 0, 0, 0);
		dataPtrLights->myLights[i].myLightPositions.Set(0, 0, 0, 0);
	}

	for (unsigned int i = 0; i < lights.size(); i++)
	{
		DX2D::Vector4f worldPos = myEngine->GetDirect3D().myCorrectedWorldWatrix.myPos4;
		
		dataPtrLights->myLights[i].myLightColors = lights[i]->myColor;
		dataPtrLights->myLights[i].myLightPositions.Set(((lights[i]->myPosition.x) - worldPos.x) * myEngine->GetWindowSize().x, ((lights[i]->myPosition.y) - worldPos.y) * myEngine->GetWindowSize().y, lights[i]->myIntensity, lights[i]->myFallOff);
	}
	dataPtrLights->myAmbience = myEngine->GetLightManager().GetAmbientLight();

	engine.GetContext()->Unmap(myLightBuffer, 0);

	engine.GetContext()->PSSetConstantBuffers(EConstantBufferSlot_Light, 1, &myLightBuffer);
	engine.GetContext()->VSSetConstantBuffers(EConstantBufferSlot_Light, 1, &myLightBuffer);
}