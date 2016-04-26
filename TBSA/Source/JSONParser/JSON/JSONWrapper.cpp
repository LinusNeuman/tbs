#include "JSONWrapper.h"
#include <fstream>
#include "../../CommonUtilities/CU/Utility/FileHandling.h"
#include "../../CommonUtilities/CU/NameSpaceAliases.h"

JSONWrapper * JSONWrapper::ourInstance = nullptr;


JSONWrapper::JSONWrapper()
{
}


JSONWrapper::~JSONWrapper()
{
}

void JSONWrapper::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new JSONWrapper();
		DL_PRINT("JSONWrapper created");
	}
	else
	{
		DL_PRINT("JSONWrapper is already created");
	}
}

void JSONWrapper::Destroy()
{
	DL_ASSERT(ourInstance != nullptr, "Trying to destroy JSONWrapper instance is nullptr");
	delete ourInstance;
	ourInstance = nullptr;
}

void JSONWrapper::SetActiveFile(const std::string aFileKey)
{
	myActiveObject = myFiles[aFileKey];
}

CU::Vector2ui JSONWrapper::GetWidthHeightUIFromActiveFile(const std::string & aElementName)
{
	return GetVectorFromFromActiveFile<unsigned int>(aElementName, "width", "height");
}

CU::Vector2ui JSONWrapper::GetPositionUIFromFromActiveFile(const std::string & aElementName, const std::string & aXName/* = "x"*/, const std::string & aYName/* = "y"*/)
{
	return GetVectorFromFromActiveFile<unsigned int>(aElementName, aXName, aYName);
}

CU::Vector2f JSONWrapper::GetPositionFloatFromActiveFile(const std::string & aElementName, const std::string & aXName /*= "x"*/, const std::string & aYName /*= "y"*/)
{
	return GetVectorFromFromActiveFile<float>(aElementName, aXName, aYName);
}

std::string JSONWrapper::GetStringFromActiveFile(const std::string & aElementName)
{
	return myActiveObject.get(aElementName).get<std::string>();
}

void JSONWrapper::SetMainDocument(const std::string & aPathToRoot)
{	
	GetInstance().myRoot = ReadJSONFile(aPathToRoot);
}

picojson::value JSONWrapper::ReadJSONFile(const std::string & aPathToFile)
{
	std::string fileContent = CU::GetFileAsString(aPathToFile);

	picojson::value tempObject;

	picojson::parse(tempObject, fileContent);

	return tempObject;
}

void JSONWrapper::InternalReadAllDocuments()
{
	picojson::object tempRoot = myRoot.get<picojson::object>();
	for (picojson::object::iterator iFile = tempRoot.begin(); iFile != tempRoot.end(); ++iFile)
	{
		myFiles[iFile->first] = ReadJSONFile(iFile->second.get<std::string>());
	}
}

void JSONWrapper::TestShitStuff()
{
	SetActiveFile("WindowSettings");
	CU::Vector2ui test = GetWidthHeightUIFromActiveFile("windowsSize");
	std::string debugLogsLocation = GetStringFromActiveFile("Logs");
	CU::Vector2f testfloat = GetPositionFloatFromActiveFile("testPosition");

	int apa = 10;
	++apa;
}