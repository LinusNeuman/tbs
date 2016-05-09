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

	template <typename TYPE>
	TYPE GetDataFromActiveFile(const std::string &aElementName);

	template <typename TYPE>
	CommonUtilities::GrowingArray<TYPE> GetArrayOfGivenTypeFromActiveFile(const std::string &anElementName);

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
	DL_ASSERT(myActiveObject.get(aElementName).is<picojson::object>(), ("JsonERROR Tavros: Can't make a vector from " + aElementName).c_str());

	picojson::object tempVectorObject = myActiveObject.get(aElementName).get<picojson::object>();

	DL_ASSERT(tempVectorObject.count(aXName) != 0, ("JsonERROR John1: json object " +aElementName+ " does not have a value called " + aXName).c_str());
	DL_ASSERT(tempVectorObject[aXName].is<double>(), ("JsonERROR Roxy1: json value" + aXName + "is not a number").c_str())

	T x = static_cast<T>(tempVectorObject[aXName].get<double>());
	T y = static_cast<T>(myActiveObject.get(aElementName).get(aYName).get<double>());

	return CU::Vector2<T>(x, y);
}

template <typename TYPE>
TYPE JSONWrapper::GetDataFromActiveFile(const std::string& aElementName)
{
	DL_ASSERT(myActiveObject.get(aElementName).is<TYPE>(), "jsonERROR Vriska:Trying to get data of the wrong type");
	return myActiveObject.get<TYPE>();
}

template <typename TYPE>
CommonUtilities::GrowingArray<TYPE> JSONWrapper::GetArrayOfGivenTypeFromActiveFile(const std::string& anElementName)
{
	picojson::value tempValue = myActiveObject.get(anElementName);

	DL_ASSERT(tempValue.is<picojson::array>(), "JsonERROR Karkat: json value is not array");

	picojson::array tempArray = tempValue.get<picojson::array>();

	CommonUtilities::GrowingArray<TYPE> returnArray;
	returnArray.Init(tempArray.size());

	for (size_t i = 0; i < tempArray.size(); i++)
	{
		DL_ASSERT(tempArray[i].is<TYPE>(), "JsonERROR Terezi: json array contains more than one value type")
		returnArray.Add(tempArray[i]);
	}

	return returnArray;
}
