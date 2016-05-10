#include "JsonWrapper.h"
#include <fstream>
#include "../../CommonUtilities/CU/DLDebug/DL_Debug.h"

JsonWrapper::JsonWrapper()
{
}


JsonWrapper::~JsonWrapper()
{
}

picojson::value JsonWrapper::LoadPicoValue(const std::string& aPath)
{
	std::ifstream jsonFile(aPath);
	DL_ASSERT(jsonFile.good() == true, ("Could not load file: " + aPath).c_str());
	picojson::value value;
	jsonFile >> value;
	jsonFile.close();
	return value;
}

picojson::object& JsonWrapper::GetPicoObject(picojson::value& aValue)
{
	DL_ASSERT(aValue.is<picojson::object>(), "Value is not an object :(");
	return aValue.get<picojson::object>();
}

picojson::array JsonWrapper::GetPicoArray(const std::string aArrayString, const picojson::object& aObject)
{
	ValidateJSONObject(aObject, aArrayString);
	return aObject.find(aArrayString)->second.get<picojson::array>();
}

const std::string JsonWrapper::GetString(const std::string& aKey, picojson::object& aObject)
{
	ValidateJSONObject(aObject, aKey);
	std::string string = aObject[aKey].get<std::string>();
	return string;
}

const CommonUtilities::Vector2f JsonWrapper::GetVector2f(const std::string& aKey1, const std::string& aKey2, picojson::object& aObject)
{
	ValidateJSONObject(aObject, aKey1);
	ValidateJSONObject(aObject, aKey2);

	float x = GetFloat(aKey1, aObject);
	float y = GetFloat(aKey2, aObject);

	return CommonUtilities::Vector2f(x, y);
}

const CommonUtilities::Vector2f JsonWrapper::GetVector2f(const std::string& aKey, picojson::object& aObject)
{
	ValidateJSONObject(aObject, aKey);
	picojson::object object = aObject[aKey].get<picojson::object>();

	float x = GetFloat("x", object);
	float y = GetFloat("y", object);

	return CommonUtilities::Vector2f(x, y);
}

double JsonWrapper::GetDouble(const std::string& aKey, picojson::object& aObject)
{
	ValidateJSONObject(aObject, aKey);
	return aObject[aKey].get<double>();
}

double JsonWrapper::GetDouble(const unsigned int aKey, picojson::array& aArray)
{
	return aArray[aKey].get<double>();
}

double JsonWrapper::GetDoubleFromString(const std::string& aKey, picojson::object& aObject)
{
	ValidateJSONObject(aObject, aKey);
	std::string tempDoubleString = aObject[aKey].get<std::string>();
	return std::stod(tempDoubleString);
}

float JsonWrapper::GetFloat(const std::string& aKey, picojson::object& aObject)
{
	return static_cast<float>(GetDouble(aKey, aObject));
}

float JsonWrapper::GetFloatFromString(const std::string& aKey, picojson::object& aObject)
{
	return static_cast<float>(GetDoubleFromString(aKey, aObject));
}

int JsonWrapper::GetInt(const std::string& aKey, picojson::object& aObject)
{
	return static_cast<int>(GetDouble(aKey, aObject));
}

int JsonWrapper::GetInt(const unsigned int aKey, picojson::array& aArray)
{
	return static_cast<int>(GetDouble(aKey, aArray));
}

int JsonWrapper::GetUnsignedInt(const unsigned int aIndex, picojson::array& aArray)
{
	return static_cast<unsigned int>(GetDouble(aIndex, aArray));
}

int JsonWrapper::GetIntFromString(const std::string& aKey, picojson::object& aObject)
{
	return static_cast<int>(GetDoubleFromString(aKey, aObject));
}

bool JsonWrapper::GetBool(const std::string& aKey, picojson::object& aObject)
{
	ValidateJSONObject(aObject, aKey);
	return aObject[aKey].get<bool>();
}


void JsonWrapper::ValidateJSONValue(const picojson::value &aValue, const std::string& aValidationString, const std::string &aPath)
{
	bool result = aValue.contains(aValidationString);
	if (result == false)
	{
		std::string message = "Error in file: " + aPath + " does not contain " + "\"" + aValidationString + "\" check spelling";
		std::cout << message << std::endl;
		DL_ASSERT(result, message.c_str());
	}
}

void JsonWrapper::ValidateJSONObject(const picojson::object &aObject, const std::string& aValidationString)
{
	bool result = aObject.find(aValidationString) != aObject.cend();
	if (result == false)
	{
		std::string message = "Error does not contain \"" + std::string(aValidationString) + "\" check spelling";
		std::cout << message << std::endl;
		DL_ASSERT(result, message.c_str());
	}
}

bool JsonWrapper::HasValue(const std::string& aKey, picojson::object& aObject)
{
	return  aObject.find(aKey) != aObject.cend();
}
