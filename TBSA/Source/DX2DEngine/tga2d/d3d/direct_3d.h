#pragma once
#include "render/render_common.h"

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11Buffer;
struct ID3D11InputLayout;
struct ID3D10Blob;
struct ID3D11SamplerState;
struct ID3D11Texture2D; 
struct ID3D11DepthStencilState;
struct ID3D11DepthStencilView;
struct ID3D11RasterizerState;
struct ID3D11DeviceChild;
struct ID3D11BlendState;
struct ID3D11Debug;
struct IDXGIAdapter;
namespace DX2D
{ 
	class CEngine;
	class CTexturedQuad;
	class CRendertarget;
	class CRenderObject;
	class CRenderObjectSprite;
	class CRenderObjectLine;
	class CTexturedQuadDrawer;
	class CLineDrawer;
	class CTexturedQuadBatch;
	class CTexturedQuadBatchDrawer;
	class CCustomShapeDrawer;
	class CRenderObjectCustom;
	class CLineMultiPrimitive;
	class CDirectEngine
	{
	public:
		CDirectEngine(void);
		~CDirectEngine(void);
		bool Init(const CEngine& aEngine, Vector2<unsigned int> aWindowSize, bool enableVSync, bool startInFullScreen);
		void PostRenderFrame();
		void RenderFrame();
		void SetClearColor(CColor aColor);
		bool CreateSampler();
		void SetWorldMatrixPosition(Vector2f aCorrectedPosition, Vector2f aPosition);
		void SetWorldMatrixZoom(float aZoom);
		ID3D11DeviceContext* GetContext() const {return myDeviceContext;}
		ID3D11Device* GetDevice() const {return myDevice;}
	
		void Draw(CRenderObject* aObject);
		void DoDraw(CRenderObjectSprite* aObject);
		void DoDraw(CRenderObjectLine* aObject);
		void DoDraw(CTexturedQuadBatch* aBatch);
		void DoDraw(CRenderObjectCustom* aCustomObject);
		void DoDraw(CLineMultiPrimitive* aObject);
		bool CompileShader(const char* aShader, const char* aMainFunction, const char* aTarget, ID3D10Blob*& aCodeBlob);
		Vector2<unsigned int> myWindowSize;

		void SetResolution(DX2D::Vector2<unsigned int> aResolution);
		void SetFullScreen(bool aFullScreen);
		void SetViewPort(float aTopLeftX, float aTopLeftY, float aWidth, float aHeight, float aMinDepth = 0.0f, float aMaxDepth = 1.0f);

		Matrix44 myCorrectedWorldWatrix;
		Matrix44 myWorldWatrix;
		Matrix44 myViewWatrix;
		Matrix44 myProjWatrix;

        int GetObjectRenderCount();


        //
        // MartinH mods
        //
        // These methods are here to facilitate running from your own update loop.
        // Use at your own risk.
        //

        // Clears the render target.
        //
        void Clear( const CColor &aColor );

	private:
		bool File_exist(const char *fileName);
		bool CollectAdapters(Vector2<unsigned int> aWindowSize, Vector2<int>& aNumDenumerator, IDXGIAdapter*& outAdapter);
		void SetShaderParametersForSprite(CRenderObjectSprite* aObject);
		void UpdateVertexes(CTexturedQuad* aQuad);
		void SetDebugObjectName(_In_ ID3D11DeviceChild* resource, _In_z_ std::string aName);

		IDXGISwapChain *mySwapchain;
		ID3D11Device *myDevice;
		ID3D11DeviceContext *myDeviceContext;
		CRendertarget* myRendertarget;
		ID3D11RenderTargetView *myBackbuffer;
		ID3D11SamplerState* mySampleState;
		ID3D11Texture2D* myDepthStencilBuffer;
		ID3D11DepthStencilState* myDepthStencilState;
		ID3D11DepthStencilView* myDepthStencilView;
		ID3D11RasterizerState* myRasterState;
		ID3D11BlendState* myAlphaEnableBlendingState;
		ID3D11Debug *myD3dDebug;
			
		int myRenderedCount;

		CTexturedQuadDrawer* myTexturedQuadDrawer;
		CCustomShapeDrawer* myCustomShapeDrawer;
		CLineDrawer* myLineDrawer;
		CTexturedQuadBatchDrawer* myTexturedQuadBatchDrawer;
		CColor myClearColor;
		int myVideoCardMemory;
		bool myEnableVSync;
	};
}