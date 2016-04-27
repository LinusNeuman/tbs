#pragma once
#include "../../CommonUtilities/CU/DLDebug/DL_Debug.h"
#include "../Pico/picojson.h"
#include "../../CommonUtilities/CU/GrowingArray/GrowingArray.h"
#include "../../CommonUtilities/CU/Vectors/vector2.h"
#include "../../CommonUtilities/CU/NameSpaceAliases.h"

class JSONWrapper
{
public:
	static void Create();
	static void Destroy();

	static void ReadAllDocuments(const std::string & aPathToRoot)
	{
		GetInstance().SetMainDocument(aPathToRoot);
		GetInstance().InternalReadAllDocuments();
	}

	static void TestShit()
	{
		GetInstance().TestShitStuff();
	}

	void SetActiveFile(const std::string aFileKey);
	CU::Vector2ui GetWidthHeightUIFromActiveFile(const std::string & aElementName);
	CU::Vector2ui GetPositionUIFromActiveFile(const std::string & aElementName, const std::string & aXName = "x", const std::string & aYName = "y");
	
	CU::Vector2f GetPositionFloatFromActiveFile(const std::string & aElementName, const std::string & aXName = "x", const std::string & aYName = "y");

	template <typename T>
	CU::Vector2<T> GetVectorFromFromActiveFile(const std::string & aElementName, const std::string & aXName = "x", const std::string & aYName = "y");

	std::string GetStringFromActiveFile(const std::string & aElementName);

private:
#pragma region Singelton
	JSONWrapper();
	~JSONWrapper();

	static JSONWrapper & GetInstance()
	{
		DL_ASSERT(ourInstance != nullptr, "JSONParser instance is nullpointer");
		return *ourInstance;
	}

	static JSONWrapper * ourInstance;
#pragma endregion
	
	void SetMainDocument(const std::string & aPathToRoot);
	picojson::value ReadJSONFile(const std::string & aPathToFile);
	void InternalReadAllDocuments();

	void TestShitStuff();
	

	picojson::value myRoot;
	picojson::value myActiveObject;
	std::map<std::string, picojson::value> myFiles;
};

template <typename T>
CU::Vector2<T>
JSONWrapper::GetVectorFromFromActiveFile(const std::string & aElementName, const std::string & aXName /*= "x"*/, const std::string & aYName /*= "y"*/)
{
	T x = static_cast<T>(myActiveObject.get(aElementName).get(aXName).get<double>());
	T y = static_cast<T>(myActiveObject.get(aElementName).get(aYName).get<double>());

	return CU::Vector2<T>(x, y);
}