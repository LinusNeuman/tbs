#pragma once

#include <string>
#include "..\Pico/picojson.h"
#include <CU/Vectors/vector2.h>

template<typename T>
class Vector;

class JsonWrapper
{
public:
	JsonWrapper();
	~JsonWrapper();

	static picojson::value LoadPicoValue(const std::string& aPath);
	static picojson::object& GetPicoObject(picojson::value& aValue);
	static picojson::array GetPicoArray(const std::string aArrayString, const picojson::object& aObject);
	 
	static const std::string GetString(const std::string& aKey, picojson::object& aObject);
	static const CommonUtilities::Vector2f GetVector2f(const std::string& aKey1, const std::string& aKey2, picojson::object& aObject);
	static const CommonUtilities::Vector2f GetVector2f(const std::string& aKey, picojson::object& aObject);
	static double GetDouble(const std::string& aKey, picojson::object& aObject);
	static double GetDouble(const unsigned int aIndex, picojson::array& aArray);
	static double GetDoubleFromString(const std::string& aKey, picojson::object& aObject);
	static float GetFloat(const std::string& aKey, picojson::object& aObject);
	static float GetFloatFromString(const std::string& aKey, picojson::object& aObject);
	static int GetInt(const std::string& aKey, picojson::object& aObject);
	static int GetInt(const unsigned int aIndex, picojson::array& aArray);
	static int GetUnsignedInt(const unsigned int aIndex, picojson::array& aArray);
	static int GetIntFromString(const std::string& aKey, picojson::object& aObject);
	static bool GetBool(const std::string& aKey, picojson::object& aObject);
	static bool HasValue(const std::string& aKey, picojson::object& aValue);
private:
	static void ValidateJSONValue(const picojson::value& aObject, const std::string& aValidationString, const std::string& aPath);
	static void ValidateJSONObject(const picojson::object& aObject, const std::string& aValidationString);
};

typedef JsonWrapper JW;