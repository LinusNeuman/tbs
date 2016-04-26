#include "stdafx.h"
#include "error/error_manager.h"
#include <iostream>
#include <cstdarg>
using namespace DX2D;


#define CONSOLE_TEXT_COLOR_RED 12
#define CONSOLE_TEXT_COLOR_YELLOW 14
#define CONSOLE_TEXT_COLOR_GREEN 10
#define CONSOLE_TEXT_COLOR_WHITE 15

CErrorManager::CErrorManager()
{
}


CErrorManager::~CErrorManager(void)
{
}


void DX2D::CErrorManager::AddLogListener(callback_function_log aFunctionToCall, callback_function_error aFunctionToCallOnError)
{
	if (aFunctionToCall)
	{
		myLogFunctions.push_back(aFunctionToCall);
	}
	if (aFunctionToCallOnError)
	{
		myErrorFunctions.push_back(aFunctionToCallOnError);
	}
}

std::string string_vsprintf(const char* format, std::va_list args)
{
	va_list tmp_args; //unfortunately you cannot consume a va_list twice
	va_copy(tmp_args, args); //so we have to copy it
	const int required_len = vsnprintf(nullptr, 0, format, tmp_args) + 1;
	va_end(tmp_args);

	std::string buf(required_len, '\0');
	if (std::vsnprintf(&buf[0], buf.size(), format, args) < 0)
	{
		return "string_vsprintf encoding error";
	}
	return buf;
}


void DX2D::CErrorManager::ErrorPrint(const char* aFile, int aline, const char* aFormat, ...)
{
	SetConsoleColor(CONSOLE_TEXT_COLOR_RED);
	std::string file = std::string(aFile);
	const size_t last_slash_idx = file.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		file.erase(0, last_slash_idx + 1);
	}

	va_list argptr;
	va_start(argptr, aFormat);
	printf("Error in %s at line:%i ", file.c_str(), aline);
	std::string str{ string_vsprintf(aFormat, argptr) };
	for (unsigned int i = 0; i < myErrorFunctions.size(); i++)
	{
		myErrorFunctions[i](str);
	}
	OutputDebugStringA(str.c_str());
	vfprintf(stderr, aFormat, argptr);
	va_end(argptr);
	std::cout << std::endl;
	SetConsoleColor(CONSOLE_TEXT_COLOR_WHITE);
}


void DX2D::CErrorManager::InfoPrint( const char* aFormat, ... )
{
	SetConsoleColor(CONSOLE_TEXT_COLOR_GREEN);
	va_list argptr;
	va_start(argptr, aFormat);

	std::string str{ string_vsprintf(aFormat, argptr) };
	for (unsigned int i = 0; i < myLogFunctions.size(); i++)
	{
		myLogFunctions[i](str);
	}

	vfprintf(stderr, aFormat, argptr);
	va_end(argptr);
	std::cout << std::endl;
	SetConsoleColor(CONSOLE_TEXT_COLOR_WHITE);
}



void DX2D::CErrorManager::InfoTip(const char* aFormat, ...)
{
	SetConsoleColor(CONSOLE_TEXT_COLOR_YELLOW);
	va_list argptr;
	va_start(argptr, aFormat);

	std::string str{ string_vsprintf(aFormat, argptr) };
	for (unsigned int i = 0; i < myLogFunctions.size(); i++)
	{
		myLogFunctions[i](str);
	}

	vfprintf(stderr, aFormat, argptr);
	va_end(argptr);
	std::cout << std::endl;
	SetConsoleColor(CONSOLE_TEXT_COLOR_WHITE);
}

void DX2D::CErrorManager::SetConsoleColor(int aColor)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!hConsole)
	{
		return;
	}
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(aColor));
}

