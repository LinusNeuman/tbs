#pragma once
#include "tga2d/Engine.h"
#include <vector>

namespace DX2D
{
	#define SETCONSOLECOLOR(color) DX2D::CEngine::GetInstance()->GetErrorManager().SetConsoleColor(color);
    #define ERROR_AUTO_PRINT(aFormat, ...) DX2D::CEngine::GetInstance()->GetErrorManager().ErrorPrint(__FILE__, __LINE__, aFormat, ##__VA_ARGS__); // same as below but badly named
	#define ERROR_PRINT(aFormat, ...) DX2D::CEngine::GetInstance()->GetErrorManager().ErrorPrint(__FILE__, __LINE__, aFormat, ##__VA_ARGS__);
    #define INFO_PRINT(aFormat, ...) DX2D::CEngine::GetInstance()->GetErrorManager().InfoPrint(aFormat, ##__VA_ARGS__);
	#define INFO_TIP(aFormat, ...) DX2D::CEngine::GetInstance()->GetErrorManager().InfoTip(aFormat, ##__VA_ARGS__);

    class CErrorManager
    {
    public:
        typedef std::function<void(std::string)> callback_function_log;
		typedef std::function<void(std::string)> callback_function_error;
        CErrorManager();
        ~CErrorManager(void);
		void AddLogListener(callback_function_log aFunctionToCall, callback_function_error aFunctionToCallOnError);
        void Destroy();
        void ErrorPrint(const char* aFile, int aline, const char* aFormat, ...);
        void InfoPrint(const char* aFormat, ...);
		void InfoTip(const char* aFormat, ...);
		void SetConsoleColor(int aColor);
    private:
		std::vector<callback_function_log> myLogFunctions;
		std::vector<callback_function_error> myErrorFunctions;
        
    };
}