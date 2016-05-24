#include "Game.h"
#include "VersionNo.h"
#include <string>
#include <stringapiset.h>

void Init();

#ifdef _DEBUG
#pragma comment(lib,"Game_Debug.lib")
#endif // DEBUG
#ifdef NDEBUG
#pragma comment(lib,"Game_Release.lib")
#endif // DEBUG
#ifdef DeMov
#pragma comment(lib,"Game_DevMode.lib")
#endif


// Comment out below define to disable command line
#define USE_CONSOLE_COMMAND

#pragma region WindowsInit
#ifdef USE_CONSOLE_COMMAND
	#pragma comment(linker, "/SUBSYSTEM:console")
#else
#pragma comment(linker, "/SUBSYSTEM:windows")
#endif

#ifdef USE_CONSOLE_COMMAND
int main()
{
	Init();
	return 0;
}
#else
int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, char*, int /*nShowCmd*/)
{	
	Init();
	return 0;
}
#endif
#pragma endregion MainFunction


static wchar_t *CharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096); 
	return wString;
}

void Init() 
{ 
	CGame myGame;
	    
	int version[] = { PRODUCTVER }; 
	std::string versionNumber;   
	 
	int count = sizeof(version) / sizeof(version[0]);  
	for (int i = 0; i < count; i++)
	{
		versionNumber += std::to_string(version[i]); 
		versionNumber += ",";
	} 
	versionNumber.pop_back();  

	myGame.Init(CharArrayToLPCWSTR(versionNumber.c_str())); 

}


