#include "stdafx.h"

#include "d3d/direct_3d.h"

#include "engine.h"
#include "drawers/custom_shape_drawer.h"
#include "drawers/line_drawer.h"
#include "drawers/textured_quad_batch_drawer.h"
#include "drawers/textured_quad_drawer.h"
#include "light/light.h"
#include "light/light_manager.h"
#include "math/common_math.h"
#include "render/render_common.h"
#include "render/render_object.h"
#include "sprite/textured_quad.h"
#include "sprite/textured_quad_batch.h"
#include "texture/texture_manager.h"
#include "windows/windows_window.h"
#include "DDSTextureLoader.h"
#include "primitives/line_primitive.h"

#include <fstream>
#include <atlcomcli.h>
#include <d3dcompiler.h>
#include <d3d11_1.h>
#include <dxgi.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")

using namespace DX2D;

const float SCREEN_DEPTH = 10.0f;
const float SCREEN_NEAR = 0.5f;

#define MAX_INSTANCES 500

#define NUM_SUPPORTED_FEATURE_LEVELS 3
const D3D_FEATURE_LEVEL supported_feature_levels[NUM_SUPPORTED_FEATURE_LEVELS] = {
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0
};
//#define REPORT_DX_WARNIGNS

CDirectEngine::CDirectEngine()
    :mySwapchain( nullptr ),
    myDevice( nullptr ),
    myDeviceContext( nullptr ),
    myBackbuffer( nullptr ),
	mySampleState(nullptr)
{
    myClearColor.myR = 0.5f;
    myClearColor.myG = 0.2f;
    myClearColor.myB = 0.4f;
    myClearColor.myA = 1.0f;
    myRenderedCount = 0;
    myEnableVSync = false;
}

CDirectEngine::~CDirectEngine( void )
{
    mySwapchain->SetFullscreenState( FALSE, NULL );    // switch to windowed mode
    myDeviceContext->ClearState();
	myDeviceContext->Flush();
    SAFE_RELEASE( mySwapchain );
    SAFE_RELEASE( myBackbuffer );
    
    SAFE_RELEASE( myDeviceContext );

    SAFE_RELEASE( myRasterState );
    SAFE_RELEASE( myDepthStencilView );
    SAFE_RELEASE( myDepthStencilState );
    SAFE_RELEASE( myDepthStencilBuffer );
    SAFE_RELEASE( myAlphaEnableBlendingState );
    SAFE_RELEASE( mySampleState );

    delete myLineDrawer;
    delete myTexturedQuadBatchDrawer;
    delete myTexturedQuadDrawer;
    delete myCustomShapeDrawer;

#ifdef REPORT_DX_WARNIGNS
	if (myD3dDebug)
    {
        myD3dDebug->ReportLiveDeviceObjects( D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL );
    }
#endif
	SAFE_RELEASE(myD3dDebug);
	SAFE_RELEASE(myDevice);
}

bool CDirectEngine::CollectAdapters(Vector2<unsigned int> aWindowSize, Vector2<int>& aNumDenumerator, IDXGIAdapter*& outAdapter)
{
    HRESULT result = S_OK;
    IDXGIFactory* factory;

    DXGI_MODE_DESC* displayModeList = nullptr;
	unsigned int numModes = 0;
	unsigned int i = 0;
	unsigned int denominator = 0;
    unsigned int numerator = 0;
    result = CreateDXGIFactory( __uuidof( IDXGIFactory ), (void**)&factory );
    if( FAILED( result ) )
    {
        return false;
    }
    // Use the factory to create an adapter for the primary graphics interface (video card).
    IDXGIAdapter* usingAdapter = nullptr;
    int adapterIndex = 0;
    std::vector<DXGI_ADAPTER_DESC> myAdapterDescs;
    std::vector<IDXGIAdapter*> myAdapters;
	while (factory->EnumAdapters(adapterIndex, &usingAdapter) != DXGI_ERROR_NOT_FOUND)
    {
        DXGI_ADAPTER_DESC adapterDesc;
		usingAdapter->GetDesc(&adapterDesc);
        myAdapterDescs.push_back( adapterDesc );
		myAdapters.push_back(usingAdapter);
        ++adapterIndex;
    }

    if( adapterIndex == 0 )
    {
        return false;
    }

    INFO_PRINT( "%s", "Video card(s) detected: " );
    for( DXGI_ADAPTER_DESC desc : myAdapterDescs )
    {
		int memory = (int)(desc.DedicatedVideoMemory / 1024 / 1024);
		INFO_PRINT("	%ls%s%i%s", desc.Description, " Mem: ", memory, "Mb");
    }

	DXGI_ADAPTER_DESC usingAdapterDesc = myAdapterDescs[0];
	usingAdapter = myAdapters[0];

	INFO_PRINT("%s", "Detecting best card...");
	

	const std::wstring nvidia = L"NVIDIA";
	const std::wstring ati = L"ATI";

	int memory = (int)(usingAdapterDesc.DedicatedVideoMemory / 1024 / 1024);
	int mostMem = 0;

	for (unsigned int i = 0; i < myAdapterDescs.size(); i++)
	{
		DXGI_ADAPTER_DESC desc = myAdapterDescs[i];
		memory = (int)(desc.DedicatedVideoMemory / 1024 / 1024);
		std::wstring name = desc.Description;
		if (name.find(nvidia) != std::wstring::npos || name.find(ati) != std::wstring::npos)
		{
			if (memory > mostMem)
			{
				mostMem = memory;
				usingAdapterDesc = desc;
				usingAdapter = myAdapters[i];
			}
		}
	}

	INFO_PRINT("%s%ls%s%i", "Using graphic card: ", usingAdapterDesc.Description, " Dedicated Mem: ", mostMem);

    // Enumerate the primary adapter output (monitor).
    IDXGIOutput* pOutput = nullptr;
	if (usingAdapter->EnumOutputs(0, &pOutput) != DXGI_ERROR_NOT_FOUND)
    {
		// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
		result = pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
		if (!FAILED(result))
		{
			// Create a list to hold all the possible display modes for this monitor/video card combination.
			displayModeList = new DXGI_MODE_DESC[numModes];
			if (displayModeList)
			{
				// Now fill the display mode list structures.
				result = pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
				if (!FAILED(result))
				{
					// Now go through all the display modes and find the one that matches the screen width and height.
					// When a match is found store the numerator and denominator of the refresh rate for that monitor.
					for (i = 0; i < numModes; i++)
					{
						if (displayModeList[i].Width == (unsigned int)aWindowSize.x)
						{
							if (displayModeList[i].Height == (unsigned int)aWindowSize.y)
							{
								numerator = displayModeList[i].RefreshRate.Numerator;
								denominator = displayModeList[i].RefreshRate.Denominator;
							}
						}
					}
				}
			}			
		}
		// Release the adapter output.
		pOutput->Release();
		pOutput = 0;
    }

   
    // Get the adapter (video card) description.
	result = usingAdapter->GetDesc(&usingAdapterDesc);
    if( FAILED( result ) )
    {
        return false;
    }

    // Store the dedicated video card memory in megabytes.
	myVideoCardMemory = (int)(usingAdapterDesc.DedicatedVideoMemory / 1024 / 1024);

    // Release the display mode list.
    delete[] displayModeList;
    displayModeList = 0;



    // Release the factory.
    factory->Release();
    factory = 0;

    if( myEnableVSync == true )
    {
        aNumDenumerator.x = numerator;
        aNumDenumerator.y = denominator;
    }
    else
    {
        aNumDenumerator.x = 0;
        aNumDenumerator.y = 1;
    }

	outAdapter = usingAdapter;
    return true;
}

bool CDirectEngine::Init(const CEngine& aEngine, Vector2<unsigned int> aWindowSize, bool enableVSync, bool startInFullScreen)
{
    myEnableVSync = enableVSync;
    HRESULT result = S_OK;

    INFO_PRINT( "%s", "Starting engine" );

    myWindowSize = aWindowSize;
    DXGI_SWAP_CHAIN_DESC swapChainDescription;
    ZeroMemory( &swapChainDescription, sizeof( DXGI_SWAP_CHAIN_DESC ) );
    // fill the swap chain description struct
    swapChainDescription.BufferCount = 1;
    swapChainDescription.BufferDesc.Width = myWindowSize.x;
    swapChainDescription.BufferDesc.Height = myWindowSize.y;
    swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    Vector2<int> numDenum;

	IDXGIAdapter* adapter = nullptr;
	if (CollectAdapters(aWindowSize, numDenum, adapter))
    {
        INFO_PRINT( "%s%s", "VSYNC Compatible: Yes, Enabled: ", myEnableVSync ? "Yes" : "No" );
    }

    swapChainDescription.BufferDesc.RefreshRate.Numerator = numDenum.x;
    swapChainDescription.BufferDesc.RefreshRate.Denominator = numDenum.y;

    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription.OutputWindow = aEngine.GetWindow().GetWindowHandle();
    swapChainDescription.SampleDesc.Count = 1;
	swapChainDescription.Windowed = !startInFullScreen;
    swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
#if defined(REPORT_DX_WARNIGNS)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
#endif
    // create a device, device context and swap chain using the information in the scd struct
    INFO_PRINT( "%s", "Creating device" );
	D3D_FEATURE_LEVEL feat_level;
	result = D3D11CreateDeviceAndSwapChain(adapter,
		D3D_DRIVER_TYPE_UNKNOWN,
        NULL,
        creationFlags,
		supported_feature_levels,
		NUM_SUPPORTED_FEATURE_LEVELS,
        D3D11_SDK_VERSION,
        &swapChainDescription,
        &mySwapchain,
        &myDevice,
		&feat_level,
        &myDeviceContext );

#if defined(_DEBUG)
	if (FAILED(result))
	{
		D3D_FEATURE_LEVEL feat_level;
		ERROR_AUTO_PRINT("%s", "Device could not create itself in debug mode, trying without debug layer... If you have Win10, try this:  Settings panel -> System -> Apps & features -> Manage optional Features -> Add a feature -> Select ""Graphics Tools""");
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		INFO_PRINT("%s", "Creating device without debug layer");
		result = D3D11CreateDeviceAndSwapChain(adapter,
			D3D_DRIVER_TYPE_UNKNOWN,
			NULL,
			creationFlags,
			supported_feature_levels,
			NUM_SUPPORTED_FEATURE_LEVELS,
			D3D11_SDK_VERSION,
			&swapChainDescription,
			&mySwapchain,
			&myDevice,
			&feat_level,
			&myDeviceContext);
	}
#endif

	if (!myDeviceContext)
	{
		ERROR_AUTO_PRINT("%s", "Device context error, you might not have a DX11 supported grahics card");
		return false;
	}

	if (FAILED(result) || !mySwapchain || feat_level == D3D_FEATURE_LEVEL_10_0)
    {
        ERROR_AUTO_PRINT( "%s", "Device swap error, you might not have a DX11 supported grahics card" );
        return false;
    }

	SetDebugObjectName(myDeviceContext, "myDeviceContext");

    myD3dDebug = nullptr;
#ifdef _DEBUG
    if( SUCCEEDED( myDevice->QueryInterface( __uuidof( ID3D11Debug ), (void**)&myD3dDebug ) ) )
    {
        ID3D11InfoQueue *d3dInfoQueue = nullptr;
        if( SUCCEEDED( myD3dDebug->QueryInterface( __uuidof( ID3D11InfoQueue ), (void**)&d3dInfoQueue ) ) )
        {
            d3dInfoQueue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_CORRUPTION, true );
            d3dInfoQueue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_ERROR, false );

            D3D11_MESSAGE_ID hide[] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // Add more message IDs here as needed
            };

            D3D11_INFO_QUEUE_FILTER filter;
            memset( &filter, 0, sizeof( filter ) );
            filter.DenyList.NumIDs = _countof( hide );
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries( &filter );
        }
    }
#endif

    // get the address of the back buffer
    ID3D11Texture2D *backBuffer = nullptr;
    result = mySwapchain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&backBuffer );
    INFO_PRINT( "%s", "Creating swapchain" );
    if( FAILED( result ) )
    {
        ERROR_AUTO_PRINT( "%s", "Get buffer error" );
        return false;
    }

    INFO_PRINT( "%s", "Swapchain created" );
    // use the back buffer address to create the render target
    result = myDevice->CreateRenderTargetView( backBuffer, NULL, &myBackbuffer );
    SetDebugObjectName( myBackbuffer, "myBackbuffer" );
    INFO_PRINT( "%s", "Creating RenderTargetView" );
    if( FAILED( result ) )
    {
        ERROR_AUTO_PRINT( "%s", "Render target view error" );
        return false;
    }
    backBuffer->Release();
    backBuffer = nullptr;

    //myRendertarget = aEngine.GetTextureManager().GetRendertarget(myWindowSize);

    D3D11_TEXTURE2D_DESC depthBufferDesc;
    // Initialize the description of the depth buffer.
    ZeroMemory( &depthBufferDesc, sizeof( depthBufferDesc ) );

    // Set up the description of the depth buffer.
    depthBufferDesc.Width = myWindowSize.x;
    depthBufferDesc.Height = myWindowSize.y;
    depthBufferDesc.MipLevels = 1;
    depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.SampleDesc.Count = 1;
    depthBufferDesc.SampleDesc.Quality = 0;
    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDesc.CPUAccessFlags = 0;
    depthBufferDesc.MiscFlags = 0;

    // Create the texture for the depth buffer using the filled out description.
    result = myDevice->CreateTexture2D( &depthBufferDesc, NULL, &myDepthStencilBuffer );
    INFO_PRINT( "%s", "Creating Texture2D" );
    if( FAILED( result ) )
    {
        ERROR_AUTO_PRINT( "%s", "Create tex2d error" );
        return false;
    }

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

    // Initialize the description of the stencil state.
    ZeroMemory( &depthStencilDesc, sizeof( depthStencilDesc ) );

    // Set up the description of the stencil state.
    depthStencilDesc.DepthEnable = false;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    depthStencilDesc.StencilEnable = true;
    depthStencilDesc.StencilReadMask = 0xFF;
    depthStencilDesc.StencilWriteMask = 0xFF;
    depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Create the depth stencil state.
    result = myDevice->CreateDepthStencilState( &depthStencilDesc, &myDepthStencilState );
    INFO_PRINT( "%s", "Creating DepthStencilState" );
    if( FAILED( result ) )
    {
        ERROR_AUTO_PRINT( "%s", "Depth stencil error" );
        return false;
    }

    myDeviceContext->OMSetDepthStencilState( myDepthStencilState, 1 );

    // Initialize the depth stencil view.
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory( &depthStencilViewDesc, sizeof( depthStencilViewDesc ) );

    // Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    // Create the depth stencil view.
    result = myDevice->CreateDepthStencilView( myDepthStencilBuffer, &depthStencilViewDesc, &myDepthStencilView );
    INFO_PRINT( "%s", "Creating DepthStencilView" );
    if( FAILED( result ) )
    {
        ERROR_AUTO_PRINT( "%s", "depth stencil view error" );
        return false;
    }

    myDeviceContext->OMSetRenderTargets( 1, &myBackbuffer, myDepthStencilView );

    D3D11_RASTERIZER_DESC rasterDesc;
    // Setup the raster description which will determine how and what polygons will be drawn.
    rasterDesc.AntialiasedLineEnable = false;
	
    rasterDesc.CullMode = D3D11_CULL_NONE;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = false;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;

    // Create the rasterizer state from the description we just filled out.
    result = myDevice->CreateRasterizerState( &rasterDesc, &myRasterState );
    INFO_PRINT( "%s", "Creating RasterizerState" );
    if( FAILED( result ) )
    {
        ERROR_AUTO_PRINT( "%s", "Resterizer error" );
        return false;
    }

    myDeviceContext->RSSetState( myRasterState );

    D3D11_BLEND_DESC blendStateDescription;
    // Clear the blend state description.
    ZeroMemory( &blendStateDescription, sizeof( D3D11_BLEND_DESC ) );
    // Create an alpha enabled blend state description.
    blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
    blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;
    result = myDevice->CreateBlendState( &blendStateDescription, &myAlphaEnableBlendingState );
    if( FAILED( result ) )
    {
        return false;
    }

    float blendFactor[4];

    // Setup the blend factor.
    blendFactor[0] = 0.0f;
    blendFactor[1] = 0.0f;
    blendFactor[2] = 0.0f;
    blendFactor[3] = 0.0f;

    // Turn on the alpha blending.
    myDeviceContext->OMSetBlendState( myAlphaEnableBlendingState, blendFactor, 0xffffffff );

	SetViewPort(0.0f, 0.0f, static_cast<float>(myWindowSize.x), static_cast<float>(myWindowSize.y));


    if( !CreateSampler() )
    {
        return false;
    }

    myTexturedQuadDrawer = new CTexturedQuadDrawer( this );
    myTexturedQuadDrawer->Init();

    myCustomShapeDrawer = new CCustomShapeDrawer( CEngine::GetInstance() );
    myCustomShapeDrawer->Init();

    myLineDrawer = new CLineDrawer( CEngine::GetInstance() );
    myLineDrawer->Init();

    myTexturedQuadBatchDrawer = new CTexturedQuadBatchDrawer( this );
    myTexturedQuadBatchDrawer->Init();

    INFO_PRINT( "%s", "All done, starting..." );
    return true;
}

void CDirectEngine::SetViewPort(float aTopLeftX, float aTopLeftY, float aWidth, float aHeight, float aMinDepth, float aMaxDepth)
{
	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = aTopLeftX;
	viewport.TopLeftY = aTopLeftY;
	viewport.Width = aWidth;
	viewport.Height = aHeight;
	viewport.MinDepth = aMinDepth;
	viewport.MaxDepth = aMaxDepth;

	myDeviceContext->RSSetViewports(1, &viewport);
}

bool CDirectEngine::CompileShader( const char* aShader, const char* aMainFunction, const char* aTarget, ID3D10Blob*& aCodeBlob )
{
    if( !File_exist( aShader ) )
    {
        ERROR_AUTO_PRINT( "%s %s", "Shader not found! ", aShader );
        return false;
    }
    HRESULT result;
    ID3D10Blob *errorMessage = nullptr;

	UINT flags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PREFER_FLOW_CONTROL;
#endif

	result = D3DCompileFromFile(DX2D::ConvertCharArrayToLPCWSTR(aShader).c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, aMainFunction, aTarget, flags, 0, &aCodeBlob, &errorMessage);
    if( FAILED( result ) )
    {
        ERROR_AUTO_PRINT( "%s %s", "Failed to compile shader: ", aShader );
    }
    LPVOID voidError = NULL;
    if( errorMessage )
    {
        voidError = errorMessage->GetBufferPointer();
        const char* errorMessage = static_cast<const char*>( voidError );
        INFO_PRINT( "%s %s", "Shader compilation error: ", errorMessage );
	
        return false;
    }
    return true;
}

bool CDirectEngine::File_exist( const char *fileName )
{
    std::ifstream infile( fileName );
	bool isGood = infile.good();
	infile.close();
	return isGood;
}

bool CDirectEngine::CreateSampler()
{
    D3D11_SAMPLER_DESC samplerDesc;
    samplerDesc.Filter = D3D11_FILTER_MAXIMUM_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    myDevice->CreateSamplerState( &samplerDesc, &mySampleState );
    myDeviceContext->PSSetSamplers( 0, 1, &mySampleState );

    return true;
}

void DX2D::CDirectEngine::PostRenderFrame()
{
    float color[4];
    color[0] = myClearColor.myR;
    color[1] = myClearColor.myG;
    color[2] = myClearColor.myB;
    color[3] = myClearColor.myA;

    myDeviceContext->ClearRenderTargetView( myBackbuffer, color );
    myDeviceContext->ClearDepthStencilView( myDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
}

void CDirectEngine::RenderFrame()
{
    if( myEnableVSync )
    {
        mySwapchain->Present( 1, 0 );
    }
    else
    {
        mySwapchain->Present( 0, 0 );
    }

    myRenderedCount = 0;
}

void DX2D::CDirectEngine::SetClearColor( CColor aColor )
{
    myClearColor = aColor;
}

void DX2D::CDirectEngine::SetWorldMatrixPosition( Vector2f aCorrectedPosition, Vector2f aPosition )
{
    myCorrectedWorldWatrix.myPos4.x = aPosition.x;
    myCorrectedWorldWatrix.myPos4.y = aPosition.y;
    myWorldWatrix.myPos4.x = aCorrectedPosition.x;
    myWorldWatrix.myPos4.y = aCorrectedPosition.y;
}

void DX2D::CDirectEngine::SetWorldMatrixZoom( float aZoom )
{
    myWorldWatrix.myPos4.z = aZoom;
}

void DX2D::CDirectEngine::Draw( CRenderObject* aObject )
{
    aObject->Draw( this );
}

void DX2D::CDirectEngine::DoDraw( CRenderObjectSprite* aObject )
{
    myTexturedQuadDrawer->Draw( aObject );
    myRenderedCount++;
}

void DX2D::CDirectEngine::DoDraw(CLineMultiPrimitive* aObject)
{
	myLineDrawer->Draw(aObject);
	myRenderedCount++;
}

void DX2D::CDirectEngine::DoDraw(CRenderObjectCustom* aCustomObject)
{
    myCustomShapeDrawer->Draw( aCustomObject );
    myRenderedCount++;
}

void  DX2D::CDirectEngine::DoDraw( CRenderObjectLine* aObject )
{
    myLineDrawer->Draw( aObject );
	myRenderedCount++;
}

void DX2D::CDirectEngine::DoDraw( CTexturedQuadBatch* aBatch )
{
    myTexturedQuadBatchDrawer->Draw( aBatch );
	myRenderedCount++;
}

void DX2D::CDirectEngine::SetDebugObjectName( _In_ ID3D11DeviceChild* resource, _In_z_ std::string aName )
{
#if defined(_DEBUG)
    resource->SetPrivateData( WKPDID_D3DDebugObjectName, static_cast<UINT>( aName.size() ), aName.c_str() );
#else
    resource;
    aName;
#endif
}

void DX2D::CDirectEngine::SetResolution( DX2D::Vector2<unsigned int> aResolution )
{
    myWindowSize = aResolution;

	CEngine::GetInstance()->myWindowSize = aResolution;
	CEngine::GetInstance()->myRenderSize = aResolution;

    myDeviceContext->OMSetRenderTargets( 0, 0, 0 );
    myBackbuffer->Release();
    HRESULT hr;
	if (!mySwapchain)
	{
		return;
	}
    hr = mySwapchain->ResizeBuffers( 0, 0, 0, DXGI_FORMAT_UNKNOWN, 0 );

	ID3D11Texture2D* pBuffer = nullptr;
    hr = mySwapchain->GetBuffer( 0, __uuidof( ID3D11Texture2D ),
        (void**)&pBuffer );

	if (!pBuffer)
	{
		return;
	}
    hr = myDevice->CreateRenderTargetView( pBuffer, NULL,
        &myBackbuffer );

    pBuffer->Release();

    myDeviceContext->OMSetRenderTargets( 1, &myBackbuffer, NULL );

	SetViewPort(0, 0, (float)myWindowSize.x, (float)myWindowSize.y);
}

void DX2D::CDirectEngine::SetFullScreen(bool aFullScreen)
{
	mySwapchain->SetFullscreenState(aFullScreen, nullptr);
}

int DX2D::CDirectEngine::GetObjectRenderCount()
{
    return myRenderedCount;
}


void DX2D::CDirectEngine::Clear( const CColor &aClearColor )
{
    myDeviceContext->ClearRenderTargetView( myBackbuffer, reinterpret_cast<const float *>( &aClearColor ) );
    myDeviceContext->ClearDepthStencilView( myDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
}
