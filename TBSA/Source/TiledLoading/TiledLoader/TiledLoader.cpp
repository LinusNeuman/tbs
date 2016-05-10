#include "stdafx.h"
#include "TiledLoader.h"
#include <JSON/JSONWrapper.h>
#include <CU/Utility/FileHandling.h>
#include <CU/DLDebug/DL_Debug.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <MapTile/MapTile.h>
#include "../../Game/Room/IsometricTile.h"

picojson::object& GetObject(picojson::value aValue);
double& GetNumber(picojson::value aValue);
picojson::array GetArray(picojson::value aValue);

void TiledLoader::Load(std::string aFilePath, CommonUtilities::GrowingArray<IsometricTile> someTiles)
{
	picojson::value root;

	std::string JsonData = CommonUtilities::GetFileAsString(aFilePath);
	std::string err = picojson::parse(root , JsonData);
	
	DL_ASSERT(err.empty(), (std::string("ERROR from Json: ") + err).c_str());

	picojson::object rootObject = GetObject(root);

	unsigned int height = static_cast<unsigned int>(GetNumber(rootObject["height"]));
	unsigned int width = static_cast<unsigned int>(GetNumber(rootObject["width"]));

	CommonUtilities::GrowingArray<MapTile> someMapTiles;

	picojson::array layers = GetArray(rootObject["layers"]);

	for (size_t i = 0; i < height * width; i++)
	{
		IsometricTile newTile = IsometricTile(CommonUtilities::Vector2f(i % width, static_cast<int>(i / height)));
		newTile.Init();
		
		for (layers)
	}

}

picojson::object& GetObject(picojson::value aValue)
{
	DL_ASSERT(aValue.is<picojson::object>(), "ERROR: Json value is not an object");
	return aValue.get<picojson::object>();
}

double& GetNumber(picojson::value aValue)
{
	DL_ASSERT(aValue.is<double>(), "ERROR: Json value is not a number");
	return aValue.get<double>();
}

picojson::array GetArray(picojson::value aValue)
{
	DL_ASSERT(aValue.is<picojson::array>(), "ERROR: Json value is not an array");
	return aValue.get<picojson::array>();
}