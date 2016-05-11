#include "stdafx.h"
#include "TiledLoader.h"
#include <JSON/JSONWrapper.h>
#include <CU/Utility/FileHandling.h>

#include "../../Game/Room/IsometricTile.h"
#include "SpriteSheet/SpriteSheet.h"
#include <JsonWrapper/JsonWrapper.h>


namespace
{
	const std::string fileEnding = ".png";
}


picojson::object GetObject(picojson::value aValue);
double& GetNumber( picojson::value aValue);
picojson::array GetArray( picojson::value aValue);
std::string GetString( picojson::value aValue);
CommonUtilities::Vector2f GetVector2f(const picojson::value& aXValue, const picojson::value& aYValue);

CommonUtilities::GrowingArray<SpriteSheet> LoadSpriteSheets(const picojson::array& aSpriteSheetArray, std::string aFileType);

void TiledLoader::Load(std::string aFilePath, CommonUtilities::GrowingArray<IsometricTile>& someTiles)
{
	picojson::value root;

	std::string JsonData = CommonUtilities::GetFileAsString(aFilePath);
	std::string err = picojson::parse(root , JsonData);
	
	DL_ASSERT(err.empty(), (std::string("ERROR from Json: ") + err).c_str());


	picojson::object rootObject = JsonWrapper::GetPicoObject(root);

	CommonUtilities::GrowingArray<SpriteSheet> SpriteSheets = LoadSpriteSheets(GetArray(rootObject["tilesets"]), fileEnding);
	SpriteSheet dataSheet;

	for (size_t i = 0; i < SpriteSheets.Size(); i++)
	{
		std::string name = SpriteSheets[i].GetName();
		if (name[0] == '_')
		{
			dataSheet = SpriteSheets[i];
			break;
		}
	}

	unsigned int height = static_cast<unsigned int>(GetNumber(rootObject["height"]));
	unsigned int width = static_cast<unsigned int>(GetNumber(rootObject["width"]));

	picojson::array layers = GetArray(rootObject["layers"]);

	for (size_t i = 0; i < height * width; i++)
	{
		IsometricTile newTile = IsometricTile(CommonUtilities::Vector2f(i % width, static_cast<int>(i / width)));
		newTile.Init();
		
		for (size_t j = 0; j < layers.size(); ++j)
		{
			picojson::object currentLayer = GetObject(layers[j]);
			std::string name = GetString(currentLayer["name"]);
			picojson::array data = GetArray(currentLayer["data"]);

			if (name[0] == '_')
			{
				unsigned int lastUnderscore = name.find_last_of('_');
				unsigned int roomId = std::stoi(name.substr(lastUnderscore + 1, name.size() - lastUnderscore));

				newTile.SetRoomId(roomId);

				int tileId = GetNumber(data[i]) - dataSheet.GetFirstIndex() + 1;
				if (tileId < 0 || tileId >= static_cast<int>(eTileType::Size))
				{
					tileId = 0;
				}

				eTileType tileType = static_cast<eTileType>(tileId);
				newTile.SetTileType(tileType);
				if (tileType == eTileType::DOOR || tileType == eTileType::DOOR_2)
				{
					newTile.SetDoor(Door(roomId));
				}
			}
			else
			{
				//todo: add code for graphics when availible
			}
		}

		someTiles.Add(newTile);
	}

}

picojson::object GetObject(picojson::value aValue)
{
	DL_ASSERT(aValue.is<picojson::object>(), "ERROR: Json value is not an object");
	return aValue.get<picojson::object>();
}

double& GetNumber(picojson::value aValue)
{
	DL_ASSERT(aValue.is<double>(), "ERROR: Json value is not a number");
	return aValue.get<double>();
}

picojson::array GetArray( picojson::value aValue)
{
	DL_ASSERT(aValue.is<picojson::array>(), "ERROR: Json value is not an array");
	return aValue.get<picojson::array>();
}

std::string GetString( picojson::value aValue)
{
	DL_ASSERT(aValue.is<std::string>(), "ERROR: Json value is not a string");
	return aValue.get<std::string>();
}

CommonUtilities::Vector2f GetVector2f(const picojson::value& aXValue, const picojson::value& aYValue)
{
	const float x = GetNumber(aXValue);
	const float y = GetNumber(aYValue);

	return CommonUtilities::Vector2f(x, y);
}

CommonUtilities::GrowingArray<SpriteSheet> LoadSpriteSheets(const picojson::array& aSpriteSheetArray, std::string aFileType)
{
	CommonUtilities::GrowingArray<SpriteSheet> returnArray;
	returnArray.Init(2);

	for (size_t i = 0; i < aSpriteSheetArray.size(); ++i)
	{
		picojson::object  currentObject = GetObject(aSpriteSheetArray[i]);

		std::string name = GetString(currentObject["name"]);
		unsigned int firstId = GetNumber(currentObject["firstgid"]);
		CommonUtilities::Vector2f size = GetVector2f(currentObject["tilewidth"], currentObject["tileheight"]);
		
		returnArray.Add(SpriteSheet(name, size, aFileType, firstId));
	}

	return returnArray;
}
