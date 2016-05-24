#include "stdafx.h"
#include "TiledLoader.h"
#include <JSON/JSONWrapper.h>
#include <CU/Utility/FileHandling.h>

//#include "../../Game/Room/IsometricTile.h"
#include <GameObjects/Room/IsometricTile.h>
#include "SpriteSheet/SpriteSheet.h"
#include <JsonWrapper/JsonWrapper.h>

#include "TiledData/TiledData.h"
#include <Rend/StaticSprite.h>

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

void TiledLoader::Load(std::string aFilePath, TiledData& someTiles)
{
	picojson::value root;
	
	std::string JsonData = CommonUtilities::GetFileAsString(aFilePath);
	std::string err = picojson::parse(root , JsonData);
	
	DL_ASSERT(err.empty(), (std::string("ERROR from Json: ") + err).c_str());


	picojson::object rootObject = JsonWrapper::GetPicoObject(root);

	CommonUtilities::GrowingArray<SpriteSheet> SpriteSheets = LoadSpriteSheets(GetArray(rootObject["tilesets"]), fileEnding);
	SpriteSheet dataSheet;
	size_t dataSheetIndex = INT_MAX;

	for (size_t i = 0; i < SpriteSheets.Size(); i++)
	{
		std::string name = SpriteSheets[i].GetName();
		if (name[0] == '_')
		{
			dataSheet = SpriteSheets[i];
			dataSheetIndex = i;
			break;
		}
	}

	unsigned int height = static_cast<unsigned int>(GetNumber(rootObject["height"]));
	unsigned int width = static_cast<unsigned int>(GetNumber(rootObject["width"]));

	picojson::array layers = GetArray(rootObject["layers"]);

	for (size_t i = 0; i < height * width; i++)
	{
		bool isOverFloor = false;
		IsometricTile newTile = IsometricTile(CommonUtilities::Vector2f(static_cast<float>(i % width), static_cast<float>(static_cast<int>(i / width))));
		newTile.Init();
		
		for (size_t j = 0; j < layers.size(); ++j)
		{
			picojson::object currentLayer = GetObject(layers[j]);
			std::string name = GetString(currentLayer["name"]);
			picojson::array data = GetArray(currentLayer["data"]);

			if (name[0] == '_')
			{
				unsigned int lastUnderscore = name.find_last_of('_');
				unsigned int roomId;
				try
				{
					roomId = std::stoi(name.substr(lastUnderscore + 1, name.size() - lastUnderscore));
				}
				catch (std::invalid_argument)
				{
					roomId = 0;
					DL_ASSERT(false, "ERROR! layers with a name starting with underscore is data layer and needs a number in the en preceeded by another underscore")
				}
				
				isOverFloor = true;
				newTile.SetRoomId(roomId);

				int tileId = static_cast<int>(GetNumber(data[i]) - dataSheet.GetFirstIndex() + 1);
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
				unsigned int tileId = static_cast<int>(GetNumber(data[i]));
				for (size_t l = 0; l < SpriteSheets.Size(); ++l)
				{
					if (tileId >= SpriteSheets[l].GetFirstIndex() && dataSheetIndex != l)
					{
						SpriteSheet explainingSpriteSheet = SpriteSheets[l];
						StaticSprite* explaingSprite = explainingSpriteSheet.CreateSprite(tileId);
						
						if (isOverFloor == true)
						{
							explaingSprite->SetLayer(enumRenderLayer::eGameObjects);
						}
						else
						{
							explaingSprite->SetLayer(enumRenderLayer::eFloor);
						}

						newTile.AddSpriteLayer(explaingSprite);
					}
				}
			}
		}

		someTiles.myTiles.Add(newTile);
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
	const float x = static_cast<float>(GetNumber(aXValue));
	const float y = static_cast<float>(GetNumber(aYValue));

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
		unsigned int firstId = static_cast<unsigned int>(GetNumber(currentObject["firstgid"]));
		CommonUtilities::Vector2f size = GetVector2f(currentObject["tilewidth"], currentObject["tileheight"]);
		CommonUtilities::Vector2f sheetSize = GetVector2f(currentObject["imageheight"], currentObject["imagewidth"]);

		returnArray.Add(SpriteSheet(name, size, sheetSize, aFileType, firstId));
	}

	return returnArray;
}
