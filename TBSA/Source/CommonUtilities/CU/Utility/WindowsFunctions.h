#pragma once
#include <windows.h>
#include "CU/Vectors/Vector4.h"
#include <iostream>

#ifdef UNICODE
	typedef std::wstring windowsString;
#else
	typedef std::string windowsString;
#endif

namespace CommonUtilities
{
	namespace WindowsFunctions
	{
		bool CheckIfWindowFullscreen(HWND aWindowID);

		Vector4f GetWindowSize(HWND aWindowID);

		windowsString CreateFolder(const windowsString & aFilePathAndFolderName);

		windowsString CreateFolder(const windowsString & aFilePath, const windowsString & aFolderName);
	}
}