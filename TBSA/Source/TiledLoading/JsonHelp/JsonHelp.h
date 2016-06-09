#pragma once
#include <Pico/picojson.h>
#include <CU/Vectors/vector2.h>
/*
*Author:  Hampus Huledal
*Date: 2016-06-09
*/


namespace JsonHelp
{
	picojson::object LoadJson(std::string aPath);
	picojson::object GetObject(picojson::value aValue);
	double& GetNumber(picojson::value aValue);
	int GetNumberInt(picojson::value aValue);
	picojson::array GetArray(picojson::value aValue);
	std::string GetString(picojson::value aValue);
	CommonUtilities::Vector2f GetVector2f(const picojson::value& aXValue, const picojson::value& aYValue);
}