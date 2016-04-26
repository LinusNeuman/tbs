#include "stdafx.h"
#include <CU/NameSpaceAliases.h>
#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <time.h>
#include <vector>
#include <CU/InputWrapper/SingletonInputWrapper.h>
#include <CU/Timer/TimeManager.h>
#include <CU/DLDebug/DL_Debug.h>
#include <JSON/JSONWrapper.h>


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
	JSONWrapper::Create();
	JSONWrapper::ReadAllDocuments("JSON/Root.json");
	JSONWrapper::TestShit();
}


CGame::~CGame()
{
	JSONWrapper::Destroy();
}


void CGame::Init(const std::wstring& aVersion)
{
	unsigned short windowWidth = 1280;
	unsigned short windowHeight = 720;


    DX2D::SEngineCreateParameters createParameters;
	createParameters.myActivateDebugSystems = DX2D::eDebugFeature_Fps | DX2D::eDebugFeature_Mem | DX2D::eDebugFeature_Filewatcher | DX2D::eDebugFeature_Cpu | DX2D::eDebugFeature_Drawcalls;
    
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = 1280;
	createParameters.myTargetHeight = 720;
	createParameters.myAutoUpdateViewportWithWindow = false;
    createParameters.myClearColor.Set( 0.0f, 0.0f, 0.0f, 1.0f );
	
	std::wstring appname = L"TGA 2D RELEASE [" + aVersion + L"]";
#ifdef _DEBUG
	appname = L"TGA 2D DEBUG  [" + aVersion + L"]";
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
	myGameWorld = new CGameWorld();

	GetInput::Create();
	GetInput::Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND());

	CU::TimeManager::Create();

	
    myGameWorld->Init();
	

	myGameStateStack.AddMainState(myGameWorld);
}


void CGame::UpdateCallBack()
{
	GetInput::Update();
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
		}
	}
}


void CGame::LogCallback( std::string aText )
{
	DL_PRINT(aText.c_str());
}