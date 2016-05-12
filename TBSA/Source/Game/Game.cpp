#include "stdafx.h"
#include <CU/NameSpaceAliases.h>
#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <time.h>
#include <vector>
//#include <CU/InputWrapper/SingletonInputWrapper.h>
#include "InputAdaption/SingletonIsometricInputWrapper.h"
#include <CU/Timer/TimeManager.h>
#include <CU/DLDebug/DL_Debug.h>
#include <JSON/JSONWrapper.h>
#include <CU/Thread/ThreadHelper.h>
#include <SingletonPostMaster.h>
#include <Rend/RenderConverter.h>
//#include "MainSingleton/MainSingleton.h"

using namespace std::placeholders;


#ifdef _DEBUG
#pragma comment(lib,"DX2DEngine_Debug.lib")
#endif // DEBUG
#ifdef NDEBUG
#pragma comment(lib,"DX2DEngine_Release.lib")
#endif // DEBUG


CGame::CGame()
{
	myImRunning = true;
	DL_Debug::Debug::Create();
	//MainSingleton::Create();
	/*JSONWrapper::Create();
	JSONWrapper::ReadAllDocuments("Data/Root.json");
	JSONWrapper::TestShit();*/
	SingletonPostMaster::Create();
	IsometricInput::Create();
}


CGame::~CGame()
{
	RenderConverter::Destroy();
}


void CGame::Init(const std::wstring& aVersion)
{
	unsigned short windowWidth = static_cast<unsigned short>(GetSystemMetrics(SM_CXSCREEN));
	unsigned short windowHeight = static_cast<unsigned short>(GetSystemMetrics(SM_CYSCREEN));


    DX2D::SEngineCreateParameters createParameters;
	createParameters.myActivateDebugSystems = DX2D::eDebugFeature_Fps | DX2D::eDebugFeature_Mem | DX2D::eDebugFeature_Filewatcher | DX2D::eDebugFeature_Cpu | DX2D::eDebugFeature_Drawcalls;
    
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = 1920;
	createParameters.myTargetHeight = 1080;
	createParameters.myAutoUpdateViewportWithWindow = true;
	createParameters.myStartInFullScreen = false;
    createParameters.myClearColor.Set(0.2f, 0.4f, 0.7f, 1.0f);

	
	std::wstring appname = L"TBS RELEASE [" + aVersion + L"]";
#ifdef _DEBUG
	appname = L"TBS DEBUG  [" + aVersion + L"]";

	createParameters.myWindowWidth = 1280;
	createParameters.myWindowHeight = 720;
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


void CGame::InitCallBack()
{
	RenderConverter::Create();
	RenderConverter::Init(CU::Vector2ui(1920, 1080));
	ThreadHelper::SetThreadName(static_cast<DWORD>(-1), "Main Thread");

	myGameWorld = new CGameWorld();

	/*GetInput::Create();
	GetInput::Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND());*/

	
	IsometricInput::Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND());
	

	CU::TimeManager::Create();

	
    myGameWorld->Init();
	

	myGameStateStack.AddMainState(myGameWorld);
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
	IsometricInput::Update();
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
	DL_PRINT(aText.c_str());
}
