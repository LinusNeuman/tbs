#include "stdafx.h"
#include <CU/NameSpaceAliases.h>
#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <time.h>
#include <vector>
#include <Input/SingletoIsometricInputWrapper/SingletonIsometricInputWrapper.h>
#include <CU/Timer/TimeManager.h>
#include <CU/DLDebug/DL_Debug.h>
#include <JSON/JSONWrapper.h>
#include <CU/Thread/ThreadHelper.h>
#include <PostMaster/SingletonPostMaster.h>
#include <Rend/RenderConverter.h>
#include <Audio/AudioManager.h>
#include <GUI/Managing/GUIFactory.h>

#include "StartupReader/StartupReader.h"
#include "StartupReader/StartupData.h"
#include <Message/StartUpLevelMessage.h>
#include <Message/GetStartLevelMessage.h>
#include <Shader/Shaders.h>
#include <tga2d/shaders/customshader.h>

#include <Message/SetHWNDMessage.h>
#include <Message/SetTargetResolutionMessage.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

using namespace std::placeholders;


#ifdef _DEBUG
#pragma comment(lib,"DX2DEngine_Debug.lib")
#endif // DEBUG
#ifdef NDEBUG
#pragma comment(lib,"DX2DEngine_Release.lib")
#endif // DEBUG


CGame::CGame()
{
	SingletonDataHolder::Create();
	DL_Debug::Debug::Create();
	StartupReader tempReader;

	myStartupData = new StartupData(tempReader.LoadAndGetStartupData());

	myImRunning = true;
	myTargetResolutionX = 0;//19-20;
	myTargetResolutionY = 0;//10-80;
	
	SingletonPostMaster::Create();
	IsometricInput::Create();

	GUIFactory::Create();
	AudioManager::Create();
	SingletonPostMaster::AddReciever(RecieverTypes::eWindowHandleChange, *this);
}


CGame::~CGame()
{
	RenderConverter::Destroy();
	SingletonDataHolder::Destroy();
}


void CGame::Init(const std::wstring& aVersion, HWND aHandle)
{
	(aHandle);

    DX2D::SEngineCreateParameters createParameters;
#ifdef _DEBUG
	//createParameters.myActivateDebugSystems = DX2D::eDebugFeature_Fps | DX2D::eDebugFeature_Mem | DX2D::eDebugFeature_Filewatcher | DX2D::eDebugFeature_Cpu | DX2D::eDebugFeature_Drawcalls;
#endif
    
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
	//From Launcher
	picojson::value value = JsonWrapper::LoadPicoValue("Settings.json");
	picojson::object settings = JsonWrapper::GetPicoObject(value);
	unsigned short windowWidth = static_cast<unsigned short>(JsonWrapper::GetInt("myResolutionX", settings));
	unsigned short windowHeight = static_cast<unsigned short>(JsonWrapper::GetInt("myResolutionY", settings));
	myTargetResolutionX = JsonWrapper::GetInt("myResolutionX", settings);
	myTargetResolutionY = JsonWrapper::GetInt("myResolutionY", settings);
	SingletonDataHolder::SetTargetResolution({myTargetResolutionX, myTargetResolutionY});

	createParameters.myWindowHeight = windowHeight;
	createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = myTargetResolutionX;
	createParameters.myTargetHeight = myTargetResolutionY;
	createParameters.myStartInFullScreen = JsonWrapper::GetBool("myIsFullscreen", settings);
	
	createParameters.myAutoUpdateViewportWithWindow = true;
    createParameters.myClearColor.Set(0.0f, 0.0f, 0.0f, 0.0f);

	
	std::wstring appname = L"TBS RELEASE [" + aVersion + L"]";
#ifdef _DEBUG
	appname = L"TBS DEBUG  [" + aVersion + L"]";

	createParameters.myWindowWidth = windowWidth;// 1280;
	createParameters.myWindowHeight = windowHeight;// 720;
	createParameters.myStartInFullScreen = false;
#endif

    createParameters.myApplicationName = appname;
    createParameters.myEnableVSync = false;

    DX2D::CEngine::CreateInstance( createParameters );

    if( !DX2D::CEngine::GetInstance()->Start() )
    {
        ERROR_AUTO_PRINT( "Fatal error! Engine could not start!" );
		system("pause");
    }


}

bool CGame::RecieveMessage(const GUIMessage & aMessage)
{
	if (aMessage.myType == RecieverTypes::eExitGame)
	{
		myImRunning = false;
		DX2D::CEngine::GetInstance()->Shutdown();
	}
	return true;
}

bool CGame::RecieveMessage(const GetStartLevelMessage & aMessage)
{
	(aMessage);
	StartUpLevelMessage startLevelMessage = StartUpLevelMessage(RecieverTypes::eStartUpLevel, myStartupData->myStartLevel);
	SendPostMessage(startLevelMessage);
	return true;
}

bool CGame::RecieveMessage(const SetHWNDMessage & aMessage)
{
	myWindowHandle = aMessage.myWindowHandle;
	return true;
}

void CGame::InitCallBack()
{
	Shaders::Create();
	DX2D::CCustomShader* customShader;
	customShader = new DX2D::CCustomShader();
	customShader->SetShaderdataFloat4(DX2D::Vector4f(0, 0, 1.f, 1.f), DX2D::EShaderDataID_1);
	customShader->PostInit("shaders/custom_sprite_vertex_shader.fx", "shaders/custom_sprite_pixel_shader.fx", DX2D::EShaderDataBufferIndex_1);

	DX2D::CCustomShader* customFoVShader;
	customFoVShader = new DX2D::CCustomShader();
	customFoVShader->SetShaderdataFloat4(DX2D::Vector4f(0, 0, 1.f, 1.f), DX2D::EShaderDataID_1);
	customFoVShader->PostInit("shaders/custom_sprite_vertex_shader.fx", "shaders/customLos_sprite_pixel_shader", DX2D::EShaderDataBufferIndex_1);

	DX2D::CCustomShader* customHighlightBlackShader;
	customHighlightBlackShader = new DX2D::CCustomShader();
	customHighlightBlackShader->SetShaderdataFloat4(DX2D::Vector4f(0, 0, 1.f, 1.f), DX2D::EShaderDataID_1);
	customHighlightBlackShader->PostInit("shaders/custom_color_vertex_shader.fx", "shaders/custom_highlightBlack_pixel_shader.fx", DX2D::EShaderDataBufferIndex_1);

	DX2D::CCustomShader* customHighlightBlueShader;
	customHighlightBlueShader = new DX2D::CCustomShader();
	customHighlightBlueShader->SetShaderdataFloat4(DX2D::Vector4f(0, 0, 1.f, 1.f), DX2D::EShaderDataID_1);
	customHighlightBlueShader->PostInit("shaders/custom_color_vertex_shader.fx", "shaders/custom_highlightBlue_pixel_shader.fx", DX2D::EShaderDataBufferIndex_1);

	DX2D::CCustomShader* customHighlightRedShader;
	customHighlightRedShader = new DX2D::CCustomShader();
	customHighlightRedShader->SetShaderdataFloat4(DX2D::Vector4f(0, 0, 1.f, 1.f), DX2D::EShaderDataID_1);
	customHighlightRedShader->PostInit("shaders/custom_color_vertex_shader.fx", "shaders/custom_highlightRed_pixel_shader.fx", DX2D::EShaderDataBufferIndex_1);

	DX2D::CCustomShader* customHighlightPurpleShader;
	customHighlightPurpleShader = new DX2D::CCustomShader();
	customHighlightPurpleShader->SetShaderdataFloat4(DX2D::Vector4f(0, 0, 1.f, 1.f), DX2D::EShaderDataID_1);
	customHighlightPurpleShader->PostInit("shaders/custom_color_vertex_shader.fx", "shaders/custom_highlightPurple_pixel_shader.fx", DX2D::EShaderDataBufferIndex_1);

	DX2D::CCustomShader* customInRangeShader;
	customInRangeShader = new DX2D::CCustomShader();
	customInRangeShader->SetShaderdataFloat4(DX2D::Vector4f(0, 0, 1.f, 1.f), DX2D::EShaderDataID_1);
	customInRangeShader->PostInit("shaders/custom_inRange_vertex_shader.fx", "shaders/custom_inRange_pixel_shader.fx", DX2D::EShaderDataBufferIndex_1);

	Shaders::GetInstance()->AddShader(customShader, "FogOfWarShader");
	Shaders::GetInstance()->AddShader(customFoVShader, "FieldOfViewShader");
	Shaders::GetInstance()->AddShader(customHighlightBlackShader, "HighlightBlackShader");
	Shaders::GetInstance()->AddShader(customHighlightBlueShader, "HighlightBlueShader");
	Shaders::GetInstance()->AddShader(customHighlightRedShader, "HighlightRedShader");
	Shaders::GetInstance()->AddShader(customHighlightPurpleShader, "HighlightPurpleShader");
	Shaders::GetInstance()->AddShader(customInRangeShader, "InRangeShader");


	SingletonPostMaster::AddReciever(RecieverTypes::eStartUpLevel, *this);

	RenderConverter::Create();
	RenderConverter::Init(CU::Vector2ui(myTargetResolutionX, myTargetResolutionY));
	ThreadHelper::SetThreadName(static_cast<DWORD>(-1), "Main Thread");

	CU::TimeManager::Create();
	GUIFactory::GetInstance()->Load();
	myMenuState = new MenuState();
	mySplashState = new SplashState();
	IsometricInput::Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND());
	myMenuState->Init();
#ifdef _DEBUG
	myGameStateStack.AddMainState(mySplashState);
#else
	myGameStateStack.AddMainState(mySplashState);
#endif
	SingletonPostMaster::AddReciever(RecieverTypes::eExitGame, *this);
	
	SendPostMessage(SetTargetResolutionMessage(RecieverTypes::eTargetResolutionSet, {myTargetResolutionX, myTargetResolutionY}));
}


void CGame::UpdateCallBack()
{
	/*myThreadPool.AddWork(Work(std::bind(&CGame::UpdateWork, this)));
	myThreadPool.AddWork(Work(std::bind(&CGame::RenderWork, this)));
	myThreadPool.Update();*/
	UpdateWork();
}

void CGame::UpdateWork()
{
	//ThreadHelper::SetThreadName(static_cast<DWORD>(-1), "ThreadPool: Update");

	if (GetActiveWindow() == myWindowHandle)
	{
		IsometricInput::Update();
	}
	else
	{
		IsometricInput::ResetInput();
	}

	CU::TimeManager::Update();


	if (myImRunning == true)
	{
		if (myGameStateStack.Update(CU::TimeManager::GetDeltaTime()) == false)
		{
			myImRunning = false;
		}
		else
		{
			myGameStateStack.Render();
			RenderWork();
		}
		//myThreadPool.Update();
	}
}

void CGame::RenderWork()
{
	RenderConverter::Draw();
	RenderConverter::SwapBuffers();
}


void CGame::LogCallback( std::string aText )
{
	//DL_PRINT(aText.c_str());
}
