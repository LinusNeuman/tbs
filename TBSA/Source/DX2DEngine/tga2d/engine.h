/*
Engine
This class is the interface between game logic and rendering. 
It takes care of creating everything necessary for window handling and rendering
*/

#pragma once
#define _X86_
#include <windef.h>

#include <functional>
#include "math/Color.h"
#include "math/vector2.h"
#include <chrono>

namespace DX2D
{
    class CWindowsWindow;
    class CDirectEngine;
    class CRenderer;
    class CTextureManager;
    class CDebugDrawer;
    class CInputManager;
    class CTextService;
    class CLightManager;
    class CErrorManager;
    class CFileWatcher;
}


namespace DX2D
{
    using callback_function        = std::function<void()>;
    using callback_function_update = std::function<void()>;
    using callback_function_log    = std::function<void( std::string )>;
    using callback_function_error  = std::function<void( std::string )>;

    enum eDebugFeatures
    {
        eDebugFeature_Fps              = 1 << 0,
        eDebugFeature_Mem              = 1 << 1,
        eDebugFeature_Drawcalls        = 1 << 2,
        eDebugFeature_Cpu              = 1 << 3,
        eDebugFeature_FpsGraph         = 1 << 4,
        eDebugFeature_Filewatcher      = 1 << 5,
        eDebugFeature_OptimiceWarnings = 1 << 6,
        eDebugFeature_All              = 1 << 7,
    };

    enum EWindowSetting
    {
        EWindowSetting_Overlapped,
        EWindowSetting_Borderless,
    };

    struct SEngineCreateParameters
    {
        SEngineCreateParameters()
        { 
            myHwnd                         = nullptr; 
            myHInstance                    = nullptr;  
            myWindowWidth                  = 800; 
            myWindowHeight                 = 600; 
            myEnableVSync                  = false; 
            myMaxRenderedObjectsPerFrame   = 100000;  // Legacy, not used
            myRenderWidth                  = myWindowWidth; 
            myRenderHeight                 = myWindowHeight; 
            myErrorFunction                = nullptr; 
            myStartInFullScreen            = false;
            myWindowSetting                = EWindowSetting_Overlapped;
            myTargetHeight                 = 0;
            myTargetWidth                  = 0;
            myAutoUpdateViewportWithWindow = false;
            myActivateDebugSystems         = 0;
        }

        callback_function myInitFunctionToCall;
        callback_function_update myUpdateFunctionToCall;
        callback_function_log myLogFunction;
        callback_function_error myErrorFunction;
        unsigned short myWindowWidth;
        unsigned short myWindowHeight;
        unsigned short myRenderWidth;
        unsigned short myRenderHeight;
        unsigned short myTargetHeight;
        unsigned short myTargetWidth;
        /* Will show the FPS and memory text*/
        int myActivateDebugSystems;
        CColor myClearColor;
        HWND *myHwnd;
        HINSTANCE myHInstance;
        std::wstring myApplicationName;
        bool myEnableVSync;
        bool myStartInFullScreen;
        int myMaxRenderedObjectsPerFrame; // Legacy, not used
        EWindowSetting myWindowSetting;
        bool myAutoUpdateViewportWithWindow;
    };


    class CEngine
    {
        friend class CTextureManager;
        friend class CRenderer;
        friend class CShader;
        friend class CErrorManager;
        friend class CDirectEngine;
    public:
        CEngine &operator =( const CEngine &anOther ) = delete;
        static void CreateInstance( const SEngineCreateParameters& aCreateParameters);
        static CEngine* GetInstance() {return myInstance;}
        static void DestroyInstance();

        bool Start();
        void Shutdown();
        
        CWindowsWindow& GetWindow() const {return *myWindow;}
        CRenderer& GetRenderer() const {return *myRenderer;}
        CTextureManager& GetTextureManager() const {return *myTextureManager;}

        CDebugDrawer& GetDebugDrawer() const {return *myDebugDrawer;}
        CInputManager& GetInputManager() const { return *myInputManager; }

        CTextService& GetTextService() const { return *myTextService; }
        CLightManager& GetLightManager() const { return *myLightManager; }

        CErrorManager& GetErrorManager() const { return *myErrorManager; }

        void SetWorldMatrixPosition( const Vector2f &aPosition);
        void SetWorldMatrixZoom(const float aZoom);
        
        Vector2ui GetWindowSize() const {return myWindowSize;}
        Vector2ui GetRenderSize() const { return myRenderSize; }
        Vector2ui GetTargetSize() const { return myTargetSize; }
        float GetWindowRatio() const;
        float GetWindowRatioInversed() const;
        CDirectEngine& GetDirect3D() const { return *myDirect3D; }

        void SetResolution(const DX2D::Vector2ui &aResolution, bool aAlsoSetWindowSize = true);

        HWND* GetHWND() const;
        HINSTANCE GetHInstance() const;

        CFileWatcher* GetFileWatcher(){ return myFileWatcher; }

        void SetViewPort(float aTopLeftX, float aTopLeftY, float aWidth, float aHeight, float aMinDepth = 0.0f, float aMaxDepth = 1.0f, bool aSetEngineResolution = false);
        //CFbxLoader* GetFBXLoader() const { return myFBXLoader; }

        void SetFullScreen(bool aFullScreen);
        bool IsDebugFeatureOn(eDebugFeatures aFeature) const;

        //
        // MartinH mods
        //
        // These methods are here to facilitate running from your own update loop.
        // Use at your own risk.
        //

        // Clears the frame and prepares engine for rendering. Run at the beginning
        // of the frame.
        //
        void BeginFrame( const CColor &aClearColor = { 0.0f, 0.0f, 0.0f, 1.0f } );

        // Passes data to GPU. Run at the end of the frame.
        //
        void EndFrame( void );

    private:
        CEngine(const SEngineCreateParameters& aCreateParameters);
        ~CEngine();

        void StartStep();
        void DoStep();
        void RunFrame();
        void CalculateRatios();

        void UpdateWindowSizeChanges();

        static CEngine* myInstance;

        callback_function_update myUpdateFunctionToCall;
        callback_function myInitFunctionToCall;
        CWindowsWindow* myWindow;
        CDirectEngine* myDirect3D;
        CRenderer* myRenderer;
        CTextureManager* myTextureManager;
        CDebugDrawer* myDebugDrawer;
        CInputManager* myInputManager;
        CTextService* myTextService;
        Vector2ui myWindowSize;
        Vector2ui myRenderSize;
        Vector2ui myTargetSize;
        Vector2ui myNativeRenderSize;
        HWND *myHwnd;
        //CFbxLoader* myFBXLoader;
        HINSTANCE myHInstance;
        CColor myClearColor;
        SEngineCreateParameters myCreateParameters;
        CLightManager* myLightManager;
        CErrorManager* myErrorManager;
        CFileWatcher* myFileWatcher;

        bool myRunEngine;
        float myWindowRatio;
        float myWindowRatioInversed;

        std::chrono::system_clock::time_point myStartOfTime;
        float myTotalTime;
        float myDeltaTime;
    };
}
