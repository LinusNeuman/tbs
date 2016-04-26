#include "stdafx.h"
#include "FileHandling.h"
#include <fstream>
#include "../DLDebug/DL_Debug.h"

std::string CommonUtilities::GetFileAsString(const std::string & aFilePath)
{
	std::ifstream filedReader(aFilePath.c_str(), std::ios::in | std::ios::binary);

	if (filedReader)
	{
		std::string contents;
		filedReader.seekg(0, std::ios::end);
		contents.resize(filedReader.tellg());
		filedReader.seekg(0, std::ios::beg);
		filedReader.read(&contents[0], contents.size());
		filedReader.close();
		return contents;
	}
	bool isFalse = false;
	DL_ASSERT(isFalse, ("Could not open " + aFilePath).c_str());
}