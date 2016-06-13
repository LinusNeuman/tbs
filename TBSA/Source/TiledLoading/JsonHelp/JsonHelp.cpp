#include <stdafx.h>
#include "JsonHelp.h"
#include <CU/Utility/FileHandling.h>

namespace JsonHelp
{
	picojson::object LoadJson(std::string aPath)
	{
		picojson::value root;

		std::string JsonData = CommonUtilities::GetFileAsString(aPath);
		std::string err = picojson::parse(root, JsonData);

		DL_ASSERT(err.empty(), (std::string("ERROR from Json: ") + err).c_str());

		return GetPicoJsonObject(root);
	}

	picojson::object GetPicoJsonObject(picojson::value aValue)
	{
		DL_ASSERT(aValue.is<picojson::object>(), "ERROR: Json value is not an object");
		return aValue.get<picojson::object>();
	}

	double& GetNumber(picojson::value aValue)
	{
		DL_ASSERT(aValue.is<double>(), "ERROR: Json value is not a number");
		return aValue.get<double>();
	}

	int GetNumberInt(picojson::value aValue)
	{
		double tempDouble = GetNumber(aValue);
		return INTCAST(tempDouble);
	};

	picojson::array GetArray(picojson::value aValue)
	{
		DL_ASSERT(aValue.is<picojson::array>(), "ERROR: Json value is not an array");
		return aValue.get<picojson::array>();
	}

	std::string GetString(picojson::value aValue)
	{
		DL_ASSERT(aValue.is<std::string>(), "ERROR: Json value is not a string");
		return aValue.get<std::string>();
	}

	CommonUtilities::Vector2f GetVector2f(const picojson::value& aXValue, const picojson::value& aYValue)
	{
		const float x = static_cast<float>(GetNumber(aXValue));
		const float y = static_cast<float>(GetNumber(aYValue));

		return CommonUtilities::Vector2f(x, y);
	}
}
